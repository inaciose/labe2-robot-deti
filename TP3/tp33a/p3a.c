#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {
      /* Code goes here */

      //rotateLeft
      setSpeed(-80,80);
      delay_ms(3000);
	  // stop
	  setSpeed(0,0);
	  delay_ms(2000);
      //rotateRight
      setSpeed(80,-80);
      delay_ms(3000);
	  // stop
	  setSpeed(0,0);
	  delay_ms(2000);
    }
  return (0);
}
