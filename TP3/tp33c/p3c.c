#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */
  int speed = 80;
  int state = 0;
  int timestop = 200;
  int timeforward = 5000;
  int timerotate = 500; // ms motors on to rotate 90 degres

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {

      // do action
      if(state == 1) {
        // go forward
        setSpeed(speed, speed);
        delay_ms(timeforward);
        setSpeed(0, 0);
        delay_ms(timestop);
        // rotate right
        setSpeed(speed, -speed);
        delay_ms(timerotate);
        setSpeed(0, 0);
        delay_ms(timestop);
       
        // go forward
        setSpeed(speed, speed);
        delay_ms(timeforward);
        setSpeed(0, 0);
        delay_ms(timestop);
        // rotate right
        setSpeed(speed, -speed);
        delay_ms(timerotate);
        setSpeed(0, 0);
        delay_ms(timestop);
        
        // go forward
        setSpeed(speed, speed);
        delay_ms(timeforward);
        setSpeed(0, 0);
        delay_ms(timestop);
        // rotate right
        setSpeed(speed, -speed);
        delay_ms(timerotate);
        setSpeed(0, 0);
        delay_ms(timestop);
        
        // go forward
        setSpeed(speed, speed);
        delay_ms(timeforward);
        setSpeed(0, 0);
        delay_ms(timestop);
        // rotate right
        //setSpeed(speed, -speed);
        //delay_ms(timerotate);
        //setSpeed(0, 0);
        //delay_ms(timestop);
        
        // stop
        state == 0;
        setSpeed(0, 0);
      }


      if(START==1 && state == 0) {
        state = 1;
        delay_ms(100);
      }

    }
  return (0);
}