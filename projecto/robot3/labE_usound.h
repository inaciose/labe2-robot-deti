/**
 * \file labE_usound.h
 * 
 * \brief C module to control an ultrassound emmitter. 
 * 
 * \author pf@ua.pt
 * \date   March 2016
 * 
 * 
 * 
 */

#ifndef LABE_USOUND_H
#define LABE_USOUND_H

#include "labE.h"

/*
 * Output pin definitions
 * 
 * If, for the ultrasound emmitter, pins other than the default
 * are to be used, modify the configs in this section.
 * 
 * Note that the definition of the output pin (USOUND_PIN_A and 
 * USOUND_PIN_B) must be coherent with the definition of the
 * direction pins (USOUND_PIN_A_DIR and USOUND_PIN_B_DIR).
 */

#define USOUND_PIN_A      Digi01      
                /**< Ultra sound ouput (pin A) */
#define USOUND_PIN_A_DIR  Digi01_Dir  
                /**< Ultra sound ouput direction bit (pin A) */

#define USOUND_PIN_B      Digi02      
                /**< Ultra sound ouput (pin B) */
#define USOUND_PIN_B_DIR  Digi02_Dir  
                /**< Ultra sound ouput direction bit (pin B) */


#define MAX_USOUND_DELAY    4*40

/**
 * \brief Initializes the PIC32 for driving the ultrassound emmitter
 * 
 * Makes all required initializations for the PIC to drive the 
 * ultrassound emmitter. 
 * 
 * The output pins are defined in USOUND_PIN_A and USOUND_PIN_B.
 * After initialization, both output pins are driven to zero, to 
 * avoid DC polarization of the emmitter.
 * 
 * Uses Timer3 for its timebase.
 */
void uSound_init(void);

/**
 * \brief Generates an ultrassound burst.
 * 
 * \arg length The burst length. Unit= 1/40kHz = 25us.
 * 
 * Generates an ultrasound burst with duration controlled by length.
 * length is expressed in periods of the 40kHz signal. 
 * 
 * At the beginning of the burst, a counter (counting periods of the 
 * ultrassound signal) is started. The counter value can be read at
 * any time by uSound_get_delay().
 */
void uSound_burst(unsigned int length);

/**
 * \brief Counts the time since the beginning of last ultrassound burst.
 * 
 * Returns the number of periods of the ultrassound signal (40kHz), 
 * since the start of the last ultrassound burst.
 */
unsigned long uSound_get_delay(void);


/**
 * \brief Counts the time since the beginning .
 * 
 * Returns the number of microseconds with 25us
 * granularity since the beginning.  
 * 
 */
unsigned long micros(void);


#endif
