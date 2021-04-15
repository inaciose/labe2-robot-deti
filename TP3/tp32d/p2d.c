#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */
  int ledid = 0;

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {
      /* Code goes here */

      // button start pressed?
      if(START==1) {
        // old led off (no led on at begin)
        if(ledid > 0) led(ledid, 0);
        // select new led
        ledid++;
        if(ledid > 4) ledid = 1;
        // new led on
        led(ledid, 1);
        // wait a little time
        delay_ms(100);
      }

      // button stop pressed?
      if(STOP==1) {
        // it is not at begin
        if(ledid > 0) {
          // current led off
          led(ledid, 0);
          delay_ms(100);          
        }
      }
    }
  return (0);
}
