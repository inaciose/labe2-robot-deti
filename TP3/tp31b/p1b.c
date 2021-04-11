#include "labE.h"

void print_time(int s) {
    int hours = 0;
    int minutes = 0;
    int seconds = 0;
    int tmp = 0;

    // calculate hours integer & remain seconds
    hours = s / 3600;
    tmp = s % 3600;

    // calculate minutes integer & remain seconds
    minutes = tmp / 60;
    seconds = tmp % 60;

    if(hours > 0) {
        printInt10(hours);
        if(hours > 1) {
            printStr(" horas");
        } else {
            printStr(" hora");
        }
    }

    if(minutes > 0) {
        // separator
        if(hours > 0) {
            if(seconds > 0) {
                printStr(", ");
            } else {
                printStr(" e ");
            }
        }
        // time
        printInt10(minutes);
        if(minutes > 1) {
            printStr(" minutos");
        } else {
            printStr(" minuto");
        }
    }

    if(seconds > 0) {
        // separator
        if(hours > 0 || minutes > 0) {
            printStr(" e ");
        }
        // time
        printInt10(seconds);
        if(seconds > 1) {
            printStr(" segundos");
        } else {
            printStr(" segundo");
        }
    }
    if(s > 0) printStr("\n");
}

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
      print_time(count);

    }
  return (0);
}
