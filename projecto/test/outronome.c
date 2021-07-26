#include "labE.h"

int
main (void)
{
  /* Variable declarations go here */
  int count = 0;

  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  while (TRUE)
    {
      /* Code goes here */

      delay_ms(1000);
      count++;
      printStr("A funcionar há ");
      printInt10(count);
      printStr("s\n");

    }
  return (0);
}
