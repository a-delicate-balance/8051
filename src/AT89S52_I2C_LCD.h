#ifndef AT89S52_I2C_LCD_H_
#define AT89S52_I2C_LCD_H_
#include "AT89S52_I2C.h"
#define LCD_ADDR (0x3F << 1)  /* PCF8574 I2C address for LCD */
#define BACKLIGHT 0x08   /* P3 controls the backlight (1 = ON, 0 = OFF)*/
/* Function Prototypes */
void I2C_LCD_Delay(unsigned int ms);
void I2C_LCD_SendCommand(unsigned char cmd);
void I2C_LCD_SendData(unsigned char datax);
void I2C_LCD_Init(void);
void I2C_LCD_Clear(void);
void I2C_LCD_SetCursor(unsigned char row, unsigned char col);
void I2C_LCD_WriteChar(char ch);
void I2C_LCD_WriteString(char *str);

void I2C_LCD_SendCommand(unsigned char cmd)
{
  /* Send High Nibble First */
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  I2C_Write((cmd & 0xF0) | BACKLIGHT);  /* Send high nibble with backlight ON */
  I2C_Stop();
  I2C_LCD_Delay(1);
  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  /* Toggle Enable HIGH and LOW */
  I2C_Write((cmd & 0xF0) | BACKLIGHT | 0x04);  /* EN = 1 */
  I2C_Stop();
 
  I2C_LCD_Delay(1);
  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  I2C_Write((cmd & 0xF0) | BACKLIGHT);         /* EN = 0 */
  I2C_Stop();
  
  I2C_LCD_Delay(1);
  
  /* Send Low Nibble Next */
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  I2C_Write(((cmd << 4) & 0xF0) | BACKLIGHT);  /* Send low nibble with backlight ON */
  I2C_Stop();
  
  I2C_LCD_Delay(1);
  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  /* Toggle Enable HIGH and LOW */
  I2C_Write(((cmd << 4) & 0xF0) | BACKLIGHT | 0x04);  /* EN = 1 */
  I2C_Stop();
  
  I2C_LCD_Delay(1);
  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  I2C_Write(((cmd << 4) & 0xF0) | BACKLIGHT);         /* EN = 0 */
  I2C_Stop();
  
  I2C_LCD_Delay(1);
}
void I2C_LCD_SendData(unsigned char datax)
{
  /* Send High Nibble First */
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  /* Send high nibble with RS=1 and backlight ON */
  I2C_Write((datax & 0xF0) | BACKLIGHT | 0x01);
  I2C_Stop();
  /* Toggle Enable HIGH and LOW */
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  I2C_Write((datax & 0xF0) | BACKLIGHT | 0x05);  /* EN = 1, RS = 1 */
  I2C_Stop();
  
  I2C_LCD_Delay(1);
  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  I2C_Write((datax & 0xF0) | BACKLIGHT | 0x01);  //* EN = 0, RS = 1 */
  I2C_Stop();
  
  I2C_LCD_Delay(1);
  /* Send Low Nibble Next */  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  /* Send low nibble with RS=1 and backlight ON */
  I2C_Write(((datax << 4) & 0xF0) | BACKLIGHT | 0x01);
  I2C_Stop();
  I2C_LCD_Delay(1);
  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  /* Toggle Enable HIGH and LOW */
  I2C_Write(((datax << 4) & 0xF0) | BACKLIGHT | 0x05);  /* EN = 1, RS = 1 */
  I2C_Stop();
  
  I2C_LCD_Delay(1);
  
  I2C_Start();
  I2C_Write(LCD_ADDR);   /* Send device address with write Bit */
  I2C_Write(((datax << 4) & 0xF0) | BACKLIGHT | 0x01);  /* EN = 0, RS = 1 */
  I2C_Stop();
  
  I2C_LCD_Delay(2);
}
void I2C_LCD_Init(void)
{
  /* Initialize the LCD in 4-Bit Mode */
  I2C_LCD_Delay(20);  /* Wait for LCD to power up */
  I2C_LCD_SendCommand(0x28);   /* 4-bit interface, 2 lines, 5x7 font */
  I2C_LCD_SendCommand(0x0C);   /* Display ON, Cursor OFF */
  I2C_LCD_SendCommand(0x06);   /* Entry mode: Increment, No shift */
  I2C_LCD_SendCommand(0x01);   /* Clear display */
  I2C_LCD_Delay(2);  /* Wait for the command to be executed */
}
void I2C_LCD_Clear(void)
{
  I2C_LCD_SendCommand(0x01);  /* Clear display */
  I2C_LCD_Delay(2);  /* Wait for the command to be executed */
}
void I2C_LCD_SetCursor(unsigned char row, unsigned char col)
{
  unsigned char address;
  if (row == 0)
  {
    address = 0x80 + col;  /* First row address */
  }
  else
  {
    address = 0xC0 + col;  /* Second row address */
  }
  I2C_LCD_SendCommand(address);  /* Set cursor to specific location */
}
void I2C_LCD_WriteChar(char ch)
{
  I2C_LCD_SendData(ch);  /* Send Data (character) to LCD */
}
void I2C_LCD_WriteString(char *str)
{
  while (*str)
  {
    I2C_LCD_WriteChar(*str);
    str++;
  }
}
void I2C_LCD_Delay(unsigned int ms)
{
  unsigned int i, j;
  for (i = 0; i < ms; i++)
  {
    for (j = 0; j < 123; j++);
  }
}
#endif
