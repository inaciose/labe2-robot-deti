/**
 * \mainpage Interfacing the MR32 platform
 *
 *	MR32 platform is aimed for Micro Rato competition
 * 
 * This library abstract the user from MR32 platform, provinding basic 
 * interfacing functions.
 * 
 */
 

/** 
 * \file labE.h
 *
 * \brief Functions for interfacing MR32 platform. 
 * 
 * Based on  mr32.h and mr32.c of J.L.Azevedo - http://sweet.ua.pt/jla/
 * 
 * Digital I/O are variables, organized by #define directives 
 * (no functions for dealing with digital I/O) 
 * 
 * \date 25-03-2014 
 * 
 **/ 

#ifndef LABE_H
#define LABE_H
 
#include <detpic32.h>

/**
 * 
 * \defgroup LogicalValues Logical Values
 * 
 * \brief Defines boolean values
 * 
 * @{
 */
#define TRUE 1					///< define TRUE, same as 1 
#define FALSE 0					///< define FALSE, same as 0 
/**@}*/

/**
 * \defgroup IO_Dir I/O Direction
 * 
 * \brief Defines IO direction (In or Out)
 * 
 * \sa BitIODir
 * 
 * @{
 */
#define OUT 0	///< Defines pin as output.
#define	IN 	1	///< Defines pin as input. 
/** @} */

/**
 * 
 * \defgroup BitIO Input and Output bits
 * 
 * \brief Defines the name of digital IO
 * 
 * These are the names of the pins available at the robot connectors
 * to be used as output or input. 
 * 
 * All the bits are programmed as inputs, by default. To turn any
 * of these pins into an output, the respective Digixx_Dir variable
 * must be set to OUT
 * 
 * \sa BitIODir, IO_Dir
 * @{
 */
 
/* CN 3 */
#define Digi01     (PORTGbits.RG7)
#define Digi02     (PORTGbits.RG8)

/* CN 8 */
#define Digi03     (PORTDbits.RD8)
#define Digi04     (PORTEbits.RE6)
#define Digi05     (PORTDbits.RD11)
#define Digi06     (PORTEbits.RE7)

/* CN 9 */
#define Digi07     (PORTDbits.RD2)
#define Digi08     (PORTDbits.RD3)
#define Digi09     (PORTDbits.RD5)
#define Digi10     (PORTDbits.RD6)
#define Digi11     (PORTEbits.RE5)
#define Digi12     (PORTDbits.RD7)

/* CN 6 */
#define Digi13     (PORTBbits.RB10)

/** @} */


/**
 * 
 * \defgroup BitIODir Input and Output bits direction
 * 
 * \brief Defines the direction (In or Out) of digital IO
 * 
 * Every digital output is, by default, programmed as Input on reset. 
 * 
 * To use a digital pin as output, the Digixx_Dir variable must be
 * set to OUT.
 * 
 * \sa IO_Dir 
 * 
 * @{ */
 
/* CN 3 */
#define Digi01_Dir     (TRISGbits.TRISG7)
#define Digi02_Dir     (TRISGbits.TRISG8)
 
/* CN 8 */
#define Digi03_Dir     (TRISDbits.TRISD8)
#define Digi04_Dir     (TRISEbits.TRISE6)
#define Digi05_Dir     (TRISDbits.TRISD11)
#define Digi06_Dir     (TRISEbits.TRISE7)

/* CN 9 */
#define Digi07_Dir     (TRISDbits.TRISD2)
#define Digi08_Dir     (TRISDbits.TRISD3)
#define Digi09_Dir     (TRISDbits.TRISD5)
#define Digi10_Dir     (TRISDbits.TRISD6)
#define Digi11_Dir     (TRISEbits.TRISE5)
#define Digi12_Dir     (TRISDbits.TRISD7)

/* CN 6 */
#define Digi13_Dir     (TRISBbits.TRISB10)

/** @} */

/**
 * \brief Possible values for analog channels. 
 * 
 * Analog inputs numbering follow the microcontroller numbering for
 * analog channels. 
 */
typedef enum { 
  Analog0=0,      /**< Analog channel #0 */
  Analog1=1,      /**< Analog channel #1 */
  Analog2=2,      /**< Analog channel #2 */
  Analog6=6,      /**< Analog channel #6 */
  Analog7=7,      /**< Analog channel #7 */
  Battery=11      /**< Analog channel #11 (Battery reading) */
} analog_chan_t;



/**
 * \defgroup Buttons Start and Stop Button
 * 
 *   Reading button macro gives the state of the button. 1 if pressed, 0 if not pressed - Active high logic
 * */
///@{ 
#define START 	(!PORTBbits.RB3)	/*!< Start Button (Black) */	
#define STOP 	(!PORTBbits.RB4)	/*!< Stop Button (Red) */
///@}

/**
 * \name LED Management
 *  	Writing 0 or 1 to LEDn macro turn off and on  the LED respectively. Reading LEDn macro gives LED state
 * */
///@{ 
#define LED1   LATEbits.LATE0 	
#define LED2   LATEbits.LATE1	
#define LED3   LATEbits.LATE2	
#define LED4   LATEbits.LATE3 	 
#define LED5   LATBbits.LATB15	
///@}



/**
 * \name Tick Flags
 * 
 * These flags are set automatically every _x_ms. Flag reset is 
 * performed by user program. 
 * 
 * Note that the time from resetting the flag to reading the flag as set
 *  is _at most_ _x_ ms, not _x_ ms.  
 */
///@{ 
extern volatile unsigned char tick10ms;     /*!< Tick flag, set every 10ms */
extern volatile unsigned char tick20ms;     /*!< Tick flag, set every 20ms */
extern volatile unsigned char tick40ms;     /*!< Tick flag, set every 40ms */
extern volatile unsigned char tick80ms;     /*!< Tick flag, set every 80ms */
extern volatile unsigned char tick160ms;     /*!< Tick flag, set every 160ms */
///@}


/* Function prototypes */

/**
 * \fn initPIC32(void)
 * 
 * \brief Performs hardware initialization
 * 
 * initPIC32() *must* be called at the start
 * of every program. Otherwise, the robot will not work!
 */
void initPIC32(void);						


/** 
 * \fn led(int LEDn, int LEDstate);
 *
 * \brief Change the state of led number _LEDn_ to LEDstate
 * 
 * LEDn is the LED ID, a number from 1 to 4. LEDsstate is 1
 * (meaning "ON") or 0 (meaning "OFF").
 * 
 * \param LEDn integer value between 1 and 4
 * \param LEDstate integer value, 0 or 1; change the state to off and on 
 * respectively
 * 
 * \returns none
 */
void led(int LEDn, int LEDstate);	


/** 
 * \fn delay_ms(unsigned int ms)
 *
 * \brief Halt the program execution for [ms] miliseconds
 * 
 * \param ms unsigned integer between [1-50.000] that corresponds to 
 * wait period in miliseconds
 * 
 * \returns none
 */
void delay_ms(unsigned int ms);				

/** 
 * \fn delay_us(unsigned int us)
 *
 * \brief Halt the program execution for [us] micrseconds
 * 
 * \param us unsigned integer between [1-50.000] that corresponds to wait 
 * period in microseconds
 * 
 * \returns none
 */
void delay_us(unsigned int ms);				

/** 
 * \fn setSpeed(int velL, int velR)
 *
 * \brief Define motor speed and direction. 
 * 
 * \param velL	Left motor speed [-100 100]	
 * \param velR 	Rigth motor speed [-100 100]
 * 
 * \returns none
 */
void setSpeed(int velL, int velR);	

/**
 * \fn unsigned int analog(analog_chan_t channel)
 * 
 * \brief Reads an analog channel 
 * 
 * Returns the value of the analog to digital conversion of the
 * voltage at the input pin.
 * 
 * Converter has 10 bits; values range from 0 (Vin=0V) to 
 * 1023 (Vin=3.3V).
 * 
 * \sa analog_chan_t
 */

unsigned int analog(analog_chan_t channel);

/**
 * \fn unsigned int battery(void)
 * 
 * \brief Returns battery voltage, in decivolts.
 * 
 * The current battery voltage is returned, in decivolts. E.g.: a value 
 * of 96 means a battery voltage of 9.6V (or 96dV). 
 * 
 * \internal 
 * The correct battery voltage depends on the correct assignment of 
 * resistor values. Battery voltage passes through a voltage divider
 * before reaching the ADC (see schematics). The resistor values are
 * defined as constants in the function body. <b> Be sure that these 
 * values match the actual resistor values in the board!</b>
 */
unsigned int battery(void);

#endif
