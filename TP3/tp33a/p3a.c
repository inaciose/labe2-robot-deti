#include "labE.h"

/*
void rotateRight()
{
  
	int i=0;
	
	for(i=0;i<100;i++)
	{
				setSpeed(i,0-i);
				delay_ms(20);
	}
	
  delay_ms(100);

	for(i=0;i<100;i++)
	{
				setSpeed(100-i,-100+i);
				delay_ms(20);
	}
  
}

void rotateLeft()
{
	int i=0;
	
	for(i=0;i<100;i++)
	{
				setSpeed(0-i,i);
				delay_ms(20);
	}
	
  delay_ms(100);

	for(i=0;i<100;i++)
	{
				setSpeed(-100+i,100-i);
				delay_ms(20);
	}
}
*/

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

      //rotateLeft();
      setSpeed(-80,80);
      delay_ms(100);
      //rotateRight();
      setSpeed(80,-80);
      delay_ms(100);

    }
  return (0);
}
