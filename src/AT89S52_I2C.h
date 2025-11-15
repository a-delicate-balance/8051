#ifndef AT89S52_I2C_H_
#define AT89S52_I2C_H_
/* Include the Main 8051 Header File */
#include <8052.h>
/* This header is necessary for using NOP */
// #include <intrins.h>
#define _nop_ __asm__("NOP");
typedef __bit Bool;

/* Define two GPIO Pins, one for SDA and one for SCL */
__sbit __at (0xA7) SDA; /* Define SDA Pin */
__sbit __at (0xA6) SCL; /* Define SDL Pin */

/* I2C Function Prototypes */
__bit I2C_Start(void);
__bit I2C_Stop(void);
__bit I2C_Write(unsigned char datax);
unsigned char I2C_Read(unsigned char ack);
/* I2C Function Definitions */
/* The I2C_Start function creates the START condition.
 * Pull SDA LOW while SCL is HIGH. */
__bit I2C_Start(void)
{
  SCL = 0;
  SDA = 1;
  _nop_;
  SCL = 1;
  _nop_;
  SDA = 0;
  _nop_;
  SCL = 0;
  return 1;
}
/* The I2C_Stop function creates the STOP condition.
 * Pull SDA HIGH while SCL is HIGH. */
__bit I2C_Stop(void)
{
  SCL = 0;
  _nop_;
  SDA = 0;
  _nop_;
  SCL = 1;
  _nop_;
  SDA = 1;
  return 1;
}
/* The I2C_Write Function Transmits one byte (8 bits) over the I2C bus.
 * The MSB (Most Significant Bit) is sent first.
 * After all 8 bits are sent, 
 * SDA is released to receive an acknowledgment (ACK)
 * from the slave. */
__bit I2C_Write(unsigned char datax)
{
  unsigned char i;
  for (i = 0; i < 8; i++)
  {
    SDA = datax & 0x80;
    _nop_;
    SCL = 1;
    _nop_;
    SCL = 0;
    datax = datax << 1;
  }
  SDA = 1;
  _nop_;
  SCL = 1;
  _nop_;
  if (SDA == 0)
  {
    SCL = 0;
    _nop_;
    return 1;
  }
  SCL = 0;
  _nop_;
  return 0;
}
/* The I2C_Read Function Reads 8 bits from the I2C slave.
 * Stores received bits in datax.
 * ACK (1) is sent if more data is expected.
 * Otherwise NACK (0) is sent. */
unsigned char I2C_Read(unsigned char ack)
{
  unsigned char i, datax = 0;
  SDA = 1;  /* Release SDA for reading */
  for (i = 0; i < 8; i++)
  {
    SCL = 1; /* Generate clock pulse */
    datax = (datax << 1) | SDA; /* Read the bit */
    SCL = 0; /* Bring SCL low */
  }
  if (ack)
  {
    SDA = 0; /* Pull SDA LOW to Send ACK */
    _nop_;
    SCL = 1; /* Generate clock for ACK */
    _nop_; /* Wait for Some time */
    SCL = 0;  /* Bring SCL low */
    _nop_;
    SDA = 1; /* Pull SDA back to HIGH */
  }
  else
  {
    SDA = 1; /* Send NACK */
    _nop_;
    SCL = 1; /* Generate clock for NACK */
    _nop_; /* Wait for Some time */
    SCL = 0;  /* Bring SCL LOW */
    _nop_; /* Wait for Some time */
    SCL = 1;
  }
  return datax; // Return the data read
}
#endif
