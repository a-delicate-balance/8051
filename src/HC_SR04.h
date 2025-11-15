#ifndef HC_SR04_H_
#define HC_SR04_H_

#include <8052.h>
#include <math.h>
#include <stdio.h>
#include <float.h>

#define sound_velocity 34300 /* sound velocity in cm per second */

#define period_in_us powf(10.0f, -6.0f)

#define Clock_period 0.667 * period_in_us /* period for clock cycle of 8051*/

__sbit __at(0x96) Trigger_pin; /* Trigger pin P2.6 */
__sbit __at(0x97) Echo_pin;    /* Echo pin    P2.7 */

void Delay_us(void);
void init_timer(void);
void send_trigger_pulse(void);

void send_trigger_pulse(void) {
  Trigger_pin = 1; /* pull trigger pin HIGH */
  Delay_us();      /* provide 10uS Delay*/
  Trigger_pin = 0; /* pull trigger pin LOW*/
}

void Delay_us(void) {
  TL0 = 0xF5;
  TH0 = 0xFF;
  TR0 = 1;
  while (TF0 == 0)
    ;
  TR0 = 0;
  TF0 = 0;
}

void init_timer(void) {
  TMOD = 0x01; /*initialize Timer*/
  TF0 = 0;
  TR0 = 0;
}

#endif
