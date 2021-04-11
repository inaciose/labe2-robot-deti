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

      // led off (macro)
      LED2 = 0;

      while(STOP==1)
      {
          // led on (macro)
          LED2 = 1;
      }      
    }
  return (0);
}
