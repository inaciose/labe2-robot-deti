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
      if(STOP==1 && ledstate != 0) {
        led(2, 0);
        delay_ms(100);
        ledstate = 0;
      }

      if(START==1 && ledstate == 0) {
        led(2, 1);
        delay_ms(100);
        ledstate = 1;
      }
    }
  return (0);
}
