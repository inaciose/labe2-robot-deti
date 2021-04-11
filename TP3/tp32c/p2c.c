#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */
  int lastbutton = 0; // debouncing ctrl
  int ledid = 1;

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {
      /* Code goes here */
      if(START==1) {
        if (lastbutton != 1) {
          // old led off
          led(ledid, 0);
          // select new led
          ledid++;
          if(ledid > 4) ledid = 1;
          // new led on
          led(ledid, 1);
          // wait
          delay_ms(100);
        }
        lastbutton = 1;
      } else {
        lastbutton = 0;
        //delay_ms(100); // realy need to wait where?
      }
    }
  return (0);
}
