#include <8052.h>
/* Include the Header File containing the PCF8574 Driver */
#include "AT89S52_I2C_LCD.h"
#include "HC_SR04.h"
#include <float.h>

#if 0
void main(void) {
  I2C_LCD_Init();                /* Initialize the LCD */
  I2C_LCD_Clear();               /* Clear the LCD */
  I2C_LCD_SetCursor(0, 0);       /* Set cursor to first row, first column */
  I2C_LCD_WriteString("Hello");  /* Write "Hello" on the first row*/
  I2C_LCD_SetCursor(1, 0);       /* Set cursor to second row */
  I2C_LCD_WriteString("World!"); /* Write "World!" on the second row */
  while (1)
    ; /* Infinite loop to keep the program running */
}
#endif

void delay(int secs) {
  for (int i = 0; i < secs * powf(10.0f, 6.0f); i++){
    Delay_us();
  }
}

void main(void) {
  unsigned char distance_in_cm[10];
  I2C_LCD_Init(); /* Initialize 16x2 LCD */
  I2C_LCD_Clear();
  I2C_LCD_SetCursor(0, 0);
  I2C_LCD_WriteString("Distance:");
  init_timer(); /* Initialize Timer*/

  while (1) {
    send_trigger_pulse(); /* send trigger pulse of 10us */

    while (!Echo_pin)
      ;      /* Waiting for Echo */
    TR0 = 1; /* Timer Starts */
    while (Echo_pin && !TF0)
      ;      /* Waiting for Echo goes LOW */
    TR0 = 0; /* Stop the timer */

    /* calculate distance using timer */
    float value = (Clock_period * (float)sound_velocity);
    float distance_measurement = (TL0 | (TH0 << 8)); /* read timer register for time count */
    distance_measurement = (distance_measurement * value) / 2.0f; /* find distance(in cm) */

    sprintf(distance_in_cm, "%.2f", distance_measurement);
    I2C_LCD_SetCursor(1, 0);
    I2C_LCD_WriteString(distance_in_cm);
    I2C_LCD_WriteString("  cm  ");

    delay(100);
  }
}
