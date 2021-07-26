#include "labE.h"
#include "labE_usound.h"
//#include <math.h>

#define SPEEDG 50       // speed go
#define SPEEDR 40       // speed rotate
#define RTIME 600       // time rotate
#define USTIMER 500000   // us period

//
// variables definition
//

unsigned long usBurstTimer;     // store next time to send a us burst
unsigned long usDelayPeriods;   // number of 25us periods to get echo
double distance;                // store the obstacle distance in meters

int isStoped = TRUE;            // robot motion status

int analogSignal;               // hold signal value
int analogLowReference = 500;   // HIGH threshold

//double airTemp = 25;            // temperature in celsius
double usPeriod = 0.000025;     // period in seconds


double aDistance[6] = {0, 0, 0, 0, 0, 0};
int iDistance = 0;
double pDistance = 0;


// velocity meters per second
// use pre-calculated values
// temp   vel m/s
// 0      332
// 10     337
// 15     340
// 20     343
// 25     346
// 30     350
double soundVelocitySec = 315; 

// receive usPeriods is tof in periods (25us each)
// return distance inn meters
double calculateDistance(unsigned long usPeriods) {
  double dist;

  // calculate distance with conversion from periods to seconds
  dist = 0.5 * (double)usPeriods * usPeriod * soundVelocitySec;

  return dist;
}

void goForward(int s) {
  setSpeed(s, s);
}

void rotateRight(int s, int d) {
  setSpeed(s, -s);
  delay_ms(d);
}

void stop() {
  setSpeed(0, 0);
  delay_ms(250);
}

int
main (void)
{
  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  /* uSound_init() initializes the oscillator hardware */
  uSound_init();

  // sound velocity calculation with conversion to kelvin
  //soundVelocitySec = 20.06 * sqrt(273.15 + airTemp);
  
  printStr("start robot\n");

  usBurstTimer = micros() + USTIMER;

  /* Main cycle */
  while (TRUE)
    {
      
      if(STOP==1) {
        led(2, 0);
        isStoped = TRUE;
        stop();
        //delay_ms(100);
      }
      
      if(START==1) {
          led(2, 1);
          isStoped = FALSE;
          delay_ms(100);
      }

      // only send the burst at
      if(micros() >= usBurstTimer) {
        usBurstTimer = micros() + USTIMER;

        /* Sends a ultrasound burst, 600us long */
        // it is 24 periods (at 40kHz)
        uSound_burst(600/25);
        
        /* Wait some time after the burst start */
        delay_us(1000);

        // do while LOW
        analogSignal = 0;
        while(analogSignal < analogLowReference) {
          // read analog port 7
          analogSignal = analog(Analog7);
          usDelayPeriods = uSound_get_delay();
          if(usDelayPeriods > 164) {
            // dont wait anymore
            break;
          }         
        }
        printStr("\n");

        distance = calculateDistance(usDelayPeriods);

        // bof: calculate average for print
        aDistance[iDistance] = distance;
        iDistance++;
        if(iDistance > 5) 
          iDistance = 0;

        int f;
        pDistance = 0;
        for(f = 0; f < 6; f++)
          pDistance += aDistance[f];

        pDistance /= 6;
        // eof: calculate average for print

        // debug
        printInt10(usDelayPeriods);
        printStr("\t");
        printInt10(pDistance * 1000);
        //printInt10(distance * 1000);
        printStr(" mm\n");
      }
      
      // check robot status
      if(isStoped) {
        continue;
      }

      // robot can move
      if(distance < 0.5) {
        // obstacle
        stop();
        rotateRight(SPEEDR, RTIME);
        stop(); 
      } else {
        //free
        goForward(SPEEDG);
      }

    }
  return (0);
}
