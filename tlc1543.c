#include <stdio.h>
#include <wiringPi.h>

#define Clock 6
#define Address 5
#define DataOut 4
#define ChipSel 21
 
unsigned int ADC_Read(unsigned char channel)
{
  unsigned int value;
  unsigned char i;
  unsigned char LSB = 0, MSB = 0;

  digitalWrite(ChipSel, 0);
  delayMicroseconds(1);
 
  channel = channel << 4;
  for (i = 0; i < 4; i ++)
  {
    if(channel & 0x80)
      digitalWrite(Address,1);
    else
      digitalWrite(Address,0);
    delayMicroseconds(1);
    digitalWrite(Clock ,1);
    delayMicroseconds(1);
    digitalWrite(Clock ,0);
    delayMicroseconds(1);
    channel = channel << 1;
  }
  for (i = 0; i < 6;i ++)
  {
    digitalWrite(Clock ,1);
    delayMicroseconds(1);
    digitalWrite(Clock ,0);
    delayMicroseconds(1);
  }
 
  delayMicroseconds(15);
  for (i = 0; i < 2; i ++)
  {
    digitalWrite(Clock ,1);
    delayMicroseconds(1);
    MSB <<= 1;
    if (digitalRead(DataOut))
      MSB |= 0x1;
    digitalWrite(Clock ,0);
    delayMicroseconds(1);
  }
  for (i = 0; i < 8; i ++)
  {
    digitalWrite(Clock ,1);
    delayMicroseconds(1);
    LSB <<= 1;
    if (digitalRead(DataOut))
      LSB |= 0x1;
    digitalWrite(Clock ,0);
    delayMicroseconds(1);
  }
  digitalWrite(ChipSel, 1);
  value = MSB;
  value <<= 8;
  value |= LSB;
  return value;
}
 
 
int main()
{
  if (wiringPiSetup() < 0)return 1 ;
 
  pinMode (DataOut,INPUT);
  pullUpDnControl(DataOut, PUD_UP);
 
  pinMode (Clock,OUTPUT);
  pinMode (Address,OUTPUT);
 
  pinMode (ChipSel,OUTPUT);
  digitalWrite (ChipSel, 1); 

  while(1)
  {
    printf("AD: %d \n",ADC_Read(8));
    printf("AD: %d \n",ADC_Read(9));
    printf("\n");
    delay(500);
    }
}

