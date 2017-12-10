#include <stdio.h>
#include <wiringPi.h>
int main (void)
{
  wiringPiSetup () ;
  pinMode (15, OUTPUT) ;
  pinMode (16, OUTPUT) ;
  for (;;)
  {
    digitalWrite (15, HIGH) ; 
	  digitalWrite (16, LOW) ;
    delay (500) ;
   
    digitalWrite (15,  LOW) ;
    digitalWrite (16, HIGH) ; 
	  delay (500) ;
  }
  return 0 ;
  //commented
}
