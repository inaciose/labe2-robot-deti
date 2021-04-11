#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */
  int lastbutton = 2; // debouncing ctrl
  int speed = 0;

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {
      
      // apply speed to motors
      setSpeed(speed, speed);
      
      /* Code goes here */
      if(STOP==1) {
        if (lastbutton != 0) {
          led(2, 0);
          speed = 0;
          delay_ms(100);
        }
        lastbutton = 0;
      }

      if(START==1) {
        if (lastbutton != 1) {
          led(2, 1);
          speed = 80;
          delay_ms(100);
        }
        lastbutton = 1;
      }

    }
  return (0);
}