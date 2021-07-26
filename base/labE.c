#include "labE.h"

/* Miscellaneous defines */

/* Motor control */ 
#define M1_IN1 LATBbits.LATB5
#define M1_IN2 LATCbits.LATC13
#define M2_IN1 LATBbits.LATB13
#define M2_IN2 LATFbits.LATF3
#define STDBY  LATCbits.LATC14		
#define M1_FORWARD M1_IN1=1; M1_IN2=0
#define M1_REVERSE M1_IN1=0; M1_IN2=1
#define M2_FORWARD M2_IN1=0; M2_IN2=1
#define M2_REVERSE M2_IN1=1; M2_IN2=0

/*
 * BATT_ARRAY_SIZE
 * 
 * Size of internal buffer for battery readings in 
 * battery().
 * 
 */
#define BATT_ARRAY_SIZE     1

volatile unsigned char tick10ms;
volatile unsigned char tick20ms;
volatile unsigned char tick40ms;
volatile unsigned char tick80ms;
volatile unsigned char tick160ms;

static int velRight=0, velLeft=0; // motor speed



/*
 * actuateMotors()
 *
 * \brief Drives motor speed and direction. Periodicly invoked, without user interaction, by Timer2 ISR (each 10 ms) 
 * 
 * \param none
 * 
 * \returns none
 */
void actuateMotors(int,int);		

/*
 * Timer2 ISR
 * 
 * According to initPIC32, Timer2 ISR is called every 10ms. 
 * 
 */
void isr_t2(void);



// ****************************************************************************
// initPIC32()
//
void initPIC32(void)
{
    int i;
    
// Disable JTAG
	DDPCON = 3;

// Config Timer2, Timer3, OC1, OC2 and OC5
	T2CONbits.TCKPS = 5;	// 1:16 prescaler (i.e. fin = 625 KHz)
	PR2 = 6249;				// Fout = 20M / (32 * (6249 + 1)) = 100 Hz
	TMR2 = 0;				// Reset timer T2 count register
	T2CONbits.TON = 1;		// Enable timer T2 (must be the last command of 
							// the timer configuration sequence)
							//
	T3CONbits.TCKPS = 4;	// 1:32 prescaler (i.e. fin = 1.25 MHz)
	PR3 = 63;				// Fout = 20M / (16 * (63 + 1)) = 20000 Hz
	TMR3 = 0;				// Reset timer T2 count register
	T3CONbits.TON = 1;		// Enable timer T2 (must be the last command of 
							// the timer configuration sequence)
// Motor1 PWM

	OC1CONbits.OCM = 6; 	// PWM mode on OCx; fault pin disabled
	OC1CONbits.OCTSEL =1;	// Use timer T3 as the time base for PWM generation
	OC1RS = 0;				// 
	OC1CONbits.ON = 1;		// Enable OC1 module

// Motor2 PWM
	OC2CONbits.OCM = 6; 	// PWM mode on OCx; fault pin disabled
	OC2CONbits.OCTSEL =1;	// Use timer T3 as the time base for PWM generation
	OC2RS = 0;				// 
	OC2CONbits.ON = 1;		// Enable OC2 module

// Servo PWM
	OC5CONbits.OCM = 6; 	// PWM mode on OCx; fault pin disabled
	OC5CONbits.OCTSEL =0;	// Use timer T2 as the time base for PWM generation
	OC5RS = 0;				// 
	OC5CONbits.ON = 1;		// Enable OC5 module


	IFS0bits.T2IF = 0;
	IPC2bits.T2IP = 1;
	IEC0bits.T2IE = 1;		// Enable Timer 2 interrupts
	IEC0bits.T2IE = 1;		

	EnableInterrupts();

// ****************************************************************************
// IO Config
//
//  1-Bridge control
	STDBY = 1;				// Half-Bridge ON

	M1_IN1 = M1_IN2 = 0;	// STOP
	M2_IN1 = M2_IN2 = 0;	// STOP

	TRISCbits.TRISC14 = OUT;	// STDBY
	TRISBbits.TRISB5 = OUT;  	// M1_IN1
	TRISCbits.TRISC13 = OUT; 	// M1_IN2

	TRISBbits.TRISB13 = OUT;  	// M2_IN1
	TRISFbits.TRISF3 = OUT;  	// M2_IN2

//  2-Leds
	LATECLR = 0x000F;		// Leds 4-1 OFF
	LATBCLR = 0x8000;		// Led 5 OFF
	TRISECLR = 0x000F;		// RE3-0 as output. RE3-0 is Leds 4-1. 
	TRISBCLR = 0x8000;		// RB15 (Led 5) as output

//  3-Sensors
	LATBbits.LATB10 = 0;		// Disable Obstacle sensors output
	TRISBbits.TRISB10 = OUT;	// EN_OBST_SENS as output
	TRISBbits.TRISB9 = IN;		// IV BEACON as input


//  Sensors in CN9 connector: RE5 and RE2-3 and RE5-7.
    LATECLR = 0x0020;			// Disable line sensor
	TRISEbits.TRISE5 = OUT;		// EN_GND_SENS as output

	LATD = LATD | 0x00EC;		// Line sensor: output latches must be set
	TRISD = TRISD & ~(0x00EC);	// Line sensor: 5 bits as output: RD2, RD3, RD5, RD6, RD7


//  4- start/stop buttons 
	CNPUE = CNPUE | 0x60;		// Activate weak pull-ups in input ports RB3 and RB4 (Start and Stop buttons)

// ADC Config
// ADC channels available in CN6, CN3 and in the board.
// CN6
	AD1PCFGbits.PCFG0 = 0;		// RB0 configured as analog input (AN0)
	AD1PCFGbits.PCFG1 = 0;		// RB1 configured as analog input (AN1)
	AD1PCFGbits.PCFG2 = 0;		// RB2 configured as analog input (AN2)
// CN3
	AD1PCFGbits.PCFG6 = 0;		// RB6 configured as analog input (AN6)
	AD1PCFGbits.PCFG7 = 0;		// RB7 configured as analog input (AN7)
// Board
	AD1PCFGbits.PCFG11 = 0;		// RB11 configured as analog input (AN11)

	AD1CON1bits.SSRC = 7;		// Conversion trigger: internal counter ends
								// sampling and starts conversion
	AD1CON1bits.CLRASAM = 1;	// Stop conversions when the 1st A/D converter
								// interrupt is generated. At the same time,
								// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16;		// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 2 - 1;	// Interrupt is generated after 2 samples
	AD1CON1bits.ON = 1;			// Enable A/D converter


	/* Fill in battery()'s internal array */
	for(i=0; i < BATT_ARRAY_SIZE; i++){
		battery();
    }

}

void delay_ms(unsigned int ms)
{
/*
 * Function:	Delay function. Stops program execution for "ms" miliseconds
 * input: 		Number of miliseconds to wait
 * output: 		None
 */
	ms = ms > 50000 ? 50000 : ms;

	resetCoreTimer();
	while(readCoreTimer() <= (20000 * ms));
}

void delay_us(unsigned int us)
{
/*
 * Function:	Delay function. Stops program execution for "us" microseconds
 * input: 		Number of microseconds to wait
 * output: 		None
 */
	us = us > 50000 ? 50000 : us; //if greather that 50.000 consider using delay_ms

	resetCoreTimer();
	while(readCoreTimer() <= (20 * us));
}

void led(int LEDn, int LEDstate)
{
/*
 * Function:	Manage LED[1-4] state
 * input: 	LEDn  - Led Number, 1 2 3 or 4
 * 			LEDst - Led State, 1 or 0
 * output: 	None
 */
 
	int mask=1;

	LEDn = LEDn < 1 ? 1 : LEDn;
	LEDn = LEDn > 4 ? 4 : LEDn;
	LEDstate = LEDstate > 0 ? 1 : 0;

	mask = mask << (LEDn - 1);
	
	if(LEDstate) //turn on
	{
		
		LATE = LATE | mask;
	}
	else // turn off
	{
		LATE = LATE & ~mask;
	}
}

void setSpeed(int velL, int velR)
{
/*
 * Function:	User API to set motor speed 
 * input: 	Left Motor Speed (velL) [0-100]
 * 			Righ Motor Speed (velR) [0-100]
 * output: 	None
 */
 
	DisableInterrupts();
	velLeft = velL;
	velRight = velR;
	EnableInterrupts();
}


void actuateMotors(int velL, int velR)
{

	velL = velL > 100 ? 100 : velL;
	velL = velL < -100 ? -100 : velL;

	velR = velR > 100 ? 100 : velR;
	velR = velR < -100 ? -100 : velR;
	
	if(velL < 0)
	{
		velL = -velL;
		M1_REVERSE;
	}
	else
	{
		M1_FORWARD;
	}

	if(velR < 0)
	{
		velR = -velR;
		M2_REVERSE;
	}
	else
	{
		M2_FORWARD;
	}
	OC1RS = ((PR3+1)*velL) / 100;
	OC2RS = ((PR3+1)*velR) / 100;

}	

unsigned int analog(analog_chan_t channel)
{
    unsigned int result;
    
	AD1CHSbits.CH0SA = channel;         // Select channel 
	AD1CON1bits.ASAM = 1;			    // Start conversion 
	while( IFS1bits.AD1IF == 0 ){};	    // Wait until AD1IF = 1
	result = (ADC1BUF0 + ADC1BUF1) / 2; // 
    IFS1bits.AD1IF = 0;                 // Clear AD1 interrupt flag
    
    return result;
}

unsigned int battery(void)
{
    /* Constants for computing a physically significant value */
    /* See schematics for circuit */
    
    /* Resistor divider */
    const int R18=10000;
    const int R19=3300;
    /* Full scale value for ADC conversion */
    const int ADC_FullScale=1023;

    /* Internal array of battery reading values */
    static unsigned char batt_readings[BATT_ARRAY_SIZE];
    static int i = 0;
    static int sum = 0;
    int value;

    /* Read battery value */
	value = analog(Battery);

    /* Adjust reading value */
	value = (value*330+511)/ADC_FullScale;
	value = (value*(R19+R18)+16500)/33000;

    /* compute the sum of last BATT_ARRAY_SIZE readings */
	sum = sum - batt_readings[i] + value;
    
    /* update most recent value in array */
	batt_readings[i] = (unsigned char)value;
    
    /* increment buffer pointer... */
	i++;
    /* ...and wrap-around if reached end of buffer */ 
    if(i>=BATT_ARRAY_SIZE)
    {
      i = 0;
    } 
    
    /* return the average of last BATT_ARRAY_SIZE readings */
	return sum / BATT_ARRAY_SIZE;
}



void _int_(_TIMER_2_VECTOR) isr_t2(void)
{
/*
 * Function:	TMR2 ISR - Motor Task 10 ms
 * input: 	None
 * output: 	None
 */
 
 	static int cntT2Ticks = 0;


	cntT2Ticks++;
	tick10ms = 1;								// Set every 10 ms
	if((cntT2Ticks % 2) == 0) tick20ms = 1;		// Set every 20 ms
	if((cntT2Ticks % 4) == 0) tick40ms = 1;		// Set every 40 ms
	if((cntT2Ticks % 8) == 0) tick80ms = 1;		// Set every 80 ms
	if((cntT2Ticks % 16) == 0) tick160ms = 1;	// Set every 160 ms

	actuateMotors(velLeft, velRight);			// velLefteft, velRight are global vars
												// set by SetVel2()

	IFS0bits.T2IF = 0;
}



