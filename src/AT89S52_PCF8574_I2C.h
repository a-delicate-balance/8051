#ifndef AT89S52_PCF8574_H_
#define AT89S52_PCF8574_H_
/* Include the I2C Header File */
#include "AT89S52_I2C.h"
/* A Static Variable for PCF8574 Address */
static unsigned char PCF8574_Address;
/* PCF8574 Function Prototypes */
void PCF8574_Init(unsigned char address);
void PCF8574_Write(unsigned char datax);
unsigned char PCF8574_Read();
void PCF8574_GPIO_Write(unsigned char pin, unsigned char value);
unsigned char PCF8574_GPIO_Read(unsigned char pin);
void PCF8574_GPIO_Toggle(unsigned char pin);
/* PCF8574 Function Definitions */
/* PCF8574_Init stores the PCF8574 I2C address for use in later functions.
 * Only called once at the beginning of the program. */
void PCF8574_Init(unsigned char address)
{
  PCF8574_Address = address << 1;
}
/* PCF8574_Write writes an 8-bit value (datax)
 * to all PCF8574 GPIO pins at once.
 * Sends I2C START, device address, data, then I2C STOP. */
void PCF8574_Write(unsigned char datax)
{
  I2C_Start();
  I2C_Write(PCF8574_Address);
  I2C_Write(datax);
  I2C_Stop();
}
/* PCF8574_Read reads 8-bit input data from PCF8574 pins.
 * The address is sent with read mode (last bit = 1).
 * The received byte is returned. */
unsigned char PCF8574_Read ()
{
  unsigned char datax;
  I2C_Start();
  I2C_Write (PCF8574_Address | 0x01); /* Read Mode */
  datax = I2C_Read(1); /* Read with ACK */
  I2C_Stop();
  return datax;
}
/* PCF8574_GPIO_Write reads the current state of all pins.
 * Modifies only the desired pin using bitwise operations.
 * Writes updated data back to the PCF8574. */
void PCF8574_GPIO_Write(unsigned char pin, unsigned char value)
{
  unsigned char datax = PCF8574_Read();
  if (value)
  {
    datax |= (1 << pin);
  }
  else
  {
    datax &= ~(1 << pin);
  }
  PCF8574_Write(datax);
}
/* PCF8574_GPIO_Read reads all GPIO pin states.
 * Extracts the requested pin value using bit masking. */
unsigned char PCF8574_GPIO_Read(unsigned char pin)
{
  unsigned char datax = PCF8574_Read();
  return (datax & (1 << pin)) ? 1 : 0;
}
/* PCF8574_GPIO_Toggle reads current pin states.
 * XOR operation flips the selected bit (0 ? 1, 1 ? 0).
 * Writes updated value back to the PCF8574. */
void PCF8574_GPIO_Toggle(unsigned char pin)
{
  unsigned char datax = PCF8574_Read();
  datax ^= (1 << pin);
  PCF8574_Write(datax);
}
#endif
