#include <8052.h>
/* Include the Header File containing the PCF8574 Driver */
#include "AT89S52_PCF8574_I2C.h"  
/* Define the Address for PCF8574 Module */
/* Adjust according to your hardware setup */
#define PCF8574_ADDRESS 0x20
/* Create a Delay Function */
void delay_ms(unsigned int ms)
{
  unsigned int i, j;
  for (i = 0; i < ms; i++)
  {
    for (j = 0; j < 120; j++);
  }
}
void main()
{
  unsigned char pin1_state = 0;
  PCF8574_Init(PCF8574_ADDRESS);
  /* Write all pins to 0xFF (all HIGH) */
  PCF8574_Write(0xFF);
  delay_ms(1000);
  /* Write all pins to 0x00 (all LOW) */
  PCF8574_Write(0x00);
  delay_ms(1000);
  while (1)
  {
    /* Toggle Pin 0 */
    PCF8574_GPIO_Toggle(0);
    delay_ms(500);
    /* Read Pin 1 state */
    pin1_state = PCF8574_GPIO_Read (1);
    /* Set Pin 2 according to Pin 1 state */
    PCF8574_GPIO_Write(2, pin1_state);
    delay_ms(10);
  }
}
