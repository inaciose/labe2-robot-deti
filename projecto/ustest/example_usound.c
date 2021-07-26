#include "labE.h"
#include "labE_usound.h"

int
main (void)
{
  /* initPIC32() makes all the required initializations to the
   * PIC32 hardware platform */
  initPIC32 ();

  printStr("start us test\n");

  /* uSound_init() initializes the oscillator hardware */
  uSound_init();

  /* Cycle to send an ultrasound burst every second */
  while (TRUE)
    {
      /* Wait 1 s */
      delay_ms(1000);
      
      /* Sends a ultrasound burst, 600us long */
      uSound_burst(600/25);
     
    }
  return (0);
}
