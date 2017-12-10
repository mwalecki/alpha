#include <stdio.h>
#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
    pinMode (0, OUTPUT) ;
    pinMode (27, INPUT) ;
    pullUpDnControl (27, PUD_OFF);
      for (;;)
        {
	  if(digitalRead (27))
	  {
            printf("yes\n");
            digitalWrite (0, HIGH) ; 
	    delay (500) ;
	  }
	  else
	  {
            printf("no\n");
            digitalWrite (0,  LOW) ; 
	    delay (500) ;
	  }
        }
      return 0 ;
}

