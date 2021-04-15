#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */
  int ledid = 0;
  // start with no led on

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {
      /* Code goes here */
      if(START==1) {
        // old led off (only if not begining)
        if(ledid > 0 ) led(ledid, 0);
        // select new led
        ledid++;
        // check last ledid and restart if needed
        if(ledid > 4) ledid = 1;
        // new led on
        led(ledid, 1);
        // wait a little time
        delay_ms(100);
      }
    }
  return (0);
}
