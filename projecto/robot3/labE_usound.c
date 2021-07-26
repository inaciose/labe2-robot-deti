/*
 * labE_usound.c
 * 
 * Copyright 2016 Pedro Fonseca <pf@ua.pt>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "labE_usound.h"

volatile unsigned long usound_counter=0;
volatile unsigned long usound_max_count=0;

volatile unsigned long micros_counter=0;

/* 
 * These definitions are solely for compatibility with stdint.h
 */
#define uint8_t unsigned int
#define uint16_t unsigned int

/* Internal definitions. */
/* These functions are used only inside labE_usound.c */

/**
 * \brief Configures Timer 3
 * 
 * \param Period    Period register (PR3) value
 * \param Prescaler Prescaler, in the range [0..7]. This is the value 
 *                  to be stored in TCKPS (T3CON<6:4>)
 * \param IntEnabled  If TRUE (!= 0), interrupts are enabled
 */
void Timer3_Configure(uint16_t Period, uint8_t Prescaler, uint8_t IntEnabled);

/**
 * \brief Starts and stops Timer 3
 * 
 * \param Running 0 disables Timer 3; 1 enables Timer 3
 * 
 * Timer 3 should have been previously configured with 
 * Timer3Configure().
 */
void Timer3_RunControl(uint8_t running);


/* 
 * Module functions
 * 
 * These are the functions in this module that are publicly available.
 */


void uSound_init(void){
  /* Set both outputs to zero (avoid DC bias): */
  USOUND_PIN_A_DIR = 0; // Output
  USOUND_PIN_B_DIR = 0; // Output
  
  /* Guarantee that ultrassound emission is off */
  usound_max_count = 0;
  usound_counter = 0;
  
  /* Configure Timer3 for generating interrupts @ 80kHz */
  Timer3_Configure(250, 0x00, 1);
  
  /* Turn Timer3 on */
  Timer3_RunControl(1);
}

/*
 * uSound_burst
 * 
 * Enables the emission of ultrassound signal by setting the 
 * usound_max_counter to twice the length (length is expressed in
 * periods of 40kHz) and reseting the usound_counter.
 */
void uSound_burst(unsigned int length)
{
  usound_max_count = 2*length;
  usound_counter = 0;
}

unsigned long uSound_get_delay(void)
{
  return usound_counter/2;
}

unsigned long micros(void)
{
  return micros_counter * 25;
}

/*
 * Private section
 * 
 * Functions below this point are internal to this file.
 */

void
Timer3_Configure (uint16_t Period, uint8_t Prescaler, uint8_t IntEnabled)
{
  PR3 = Period;			/* Timer 3 Period register */
  TMR3 = 0;			/* Reset Timer 3 Counter */

  T3CONbits.TGATE = 0;
  T3CONbits.TCS = 0;
  T3CONbits.TCKPS = Prescaler;

  IFS0bits.T3IF = 0;
  IPC3bits.T3IP = 5;
  if (IntEnabled) {
    IEC0bits.T3IE = 1;		/* Enable T3 Interrupts */
  }
  
  T3CONbits.TON = 0;

}


void
Timer3_RunControl (uint8_t running)
{
  if (running == 0) {
    /* Disable Timer 3 */
    T3CONbits.TON = 0;
  }
  else {
    /* Enable Timer 3 */
    T3CONbits.TON = 1;
  }
}

void
_int_ (_TIMER_3_VECTOR)
isr_t3 (void)
{
  /* Memory for recalling last state */
  /* Required for toggling output */
  static volatile unsigned int mem; 

  /* Increment us time counter. */
  micros_counter++;
  
  /* Increment ultrassound half-periods counter.
   * 
   * Testing againts MAX_USOUND_DELAY freezes the counter
   * (no more increments) and prevents wrapping around */
   if(usound_counter <= 2*MAX_USOUND_DELAY+10){
    usound_counter++;
  }
  
  /* If usound_counter has not reached max_count,
   * continue transmitting the signal */
  if(usound_counter < usound_max_count){
    if (mem == 0) {
      mem = 1;
      USOUND_PIN_A = 1;
      USOUND_PIN_B = 0;
    }
    else {
      mem = 0;
      USOUND_PIN_A = 0;
      USOUND_PIN_B = 1;
    }
  }
  else {
    /* if usound_counter has reached max_count, silent the output */
    USOUND_PIN_A = 0;
    USOUND_PIN_B = 0;
  }

  /* Clear Timer3 Interrupt Flag */
  IFS0bits.T3IF = 0;
}

