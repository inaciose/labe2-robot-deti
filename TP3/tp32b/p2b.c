#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */
  int ledstate = 0; // debouncing ctrl

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {
      /* Code goes here */

      // check if led is on and stop pressed
      // if true put led off
      if(STOP==1 && ledstate != 0) {
        led(2, 0);
        ledstate = 0;
      }

      // check if led is off and start pressed
      // if true put led on
      if(START==1 && ledstate == 0) {
        led(2, 1);
        ledstate = 1;
      }
    }
  return (0);
}
