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
        // the two wheels rotate forward with 
        // velocity in speed variable, 
        // for time in timeforward variable
        setSpeed(speed, speed);
        delay_ms(timeforward);
        // stop (velocity = 0) for the time in timestop variable
        setSpeed(0, 0);
        delay_ms(timestop);

        // rotate right
        // left wheel rotate forward at velocity in speed variable, 
        // right wheel rotate backward at velocity in speed variable,
        // the wheels rotate for the time in timerotate then stop
        // its assumed that for this wheels directions and time the robot
        // rotate 90 degrees right
        setSpeed(speed, -speed);
        delay_ms(timerotate);
        // stop (velocity = 0) for the time in timestop variable
        setSpeed(0, 0);
        delay_ms(timestop);
       
        // go forward
        // (described above)
        setSpeed(speed, speed);
        delay_ms(timeforward);
        setSpeed(0, 0);
        delay_ms(timestop);

        // rotate right
        // (described above)
        setSpeed(speed, -speed);
        delay_ms(timerotate);
        setSpeed(0, 0);
        delay_ms(timestop);
        
        // go forward
        // (described above)
        setSpeed(speed, speed);
        delay_ms(timeforward);
        setSpeed(0, 0);
        delay_ms(timestop);

        // rotate right
        // (described above)
        setSpeed(speed, -speed);
        delay_ms(timerotate);
        setSpeed(0, 0);
        delay_ms(timestop);
        
        // go forward
        // (described above)
        setSpeed(speed, speed);
        delay_ms(timeforward);
        setSpeed(0, 0);
        delay_ms(timestop);
        // rotate right
        //setSpeed(speed, -speed);
        //delay_ms(timerotate);
        //setSpeed(0, 0);
        //delay_ms(timestop);
        
        // round complete
        state = 0;
      }

      if(START==1 && state == 0) {
        state = 1;
        delay_ms(100);
      }

    }
  return (0);
}
