#include "labE.h"
#include "labE_usound.h"
//#include <math.h>

#define SPEEDG 30
#define SPEEDR 30

//
// variables definition
//

//int isObstacleAhead = false;
int isStoped = TRUE;

int analogSignal;               // hold signal value
int analogLowReference = 400;   // HIGH threshold

//double airTemp = 25;            // temperature in celsius
double usPeriod = 0.000025;     // period in seconds

// velocity meters per second
// use pre-calculated values
// temp   vel m/s
// 0      332
// 10     337
// 15     340
// 20     343
// 25     346
// 30     350
double soundVelocitySec = 346; 

double distance;                // distance meters

double getDistanceFromSonar() {
  
  double dist;                    // distance meters
  unsigned long usDelayPeriods;   // us tof in periods

  // we got some signal, get tof
  // expressed in periods
  // each period is 25us
  usDelayPeriods = uSound_get_delay();

  //printInt10(usDelayPeriods);
  //printStr("\t");

  // calculate distance with conversion from periods to seconds
  dist = 0.5 * (double)usDelayPeriods * usPeriod * soundVelocitySec;

  //printInt10(dist * 1000000);
  //printStr("\n");

  return dist;
}

void goForward(int s) {
  setSpeed(s, s);
}

void rotateRight(int s, int d) {
  setSpeed(s, -s);
  delay_ms(d);
}

/*
void rotateLeft(int s, int d) {
  setSpeed(-s, s);
  delay_ms(d);
}

void goBackward(int s) {
  setSpeed(-s, -s);
}
*/

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
  
  printStr("start\n");

  // some temporary vars
  unsigned long tmp;

  /* Main cycle */
  while (TRUE)
    {
      
      if(STOP==1) {
        led(2, 0);
        isStoped = 1;
        stop();
        //delay_ms(100);
      }
      
      if(START==1) {
          led(2, 1);
          isStoped = 0;
          delay_ms(100);
      }

      /* Wait some time */
      delay_ms(10);

      /* Sends a ultrasound burst, 600us long */
      // it is 24 periods (at 40kHz)
      uSound_burst(600/25);

      // while LOW
      analogSignal = 0;
      while(analogSignal < analogLowReference) {
        // read analog port 7
        analogSignal=analog(Analog7);
        tmp = uSound_get_delay();
        if(tmp > 164) {
          break;
        }
        
        //printStr("loop ");
        //printInt10(tmp);
        //printStr("\t");
        printInt10(analogSignal);
        printStr("\n");
        //*/
        
      }
      //printStr("ok\n");
      //while(1) {}

      distance = getDistanceFromSonar();

      
      printInt10(tmp);
      printStr("\t");
      printInt10(distance * 100);
      printStr("\n");
      

      // check robot status
      if(isStoped) {
        continue;
      }

      // robot can move
      if(distance < 0.5) {
        //isObstacleAhead = 1;
        stop();
        rotateRight(SPEEDR, 1200);
        stop();
        
      } else {
        //isObstacleAhead = 0;
        goForward(SPEEDG);
      }

    }
  return (0);
}
