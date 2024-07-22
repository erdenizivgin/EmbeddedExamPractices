#include "avr/io.h"
#include "avr/interrupt.h"
#include "timer.h"
#include "led.h"

#define LEDPIN PB5
#define LEDPORT PORTB
#define LEDDDR DDRB

static volatile int count = 0;

void blinkLed(void)
{

  count++;
  // For loop to toggle the builtin led to toggle every 1 sec
  if (count >= 1000)
  {
    count = 0;
    led_builtinToggle();
  }
}

int main(void)
{
  led_builtinInit();
  timer0_setCallback(&blinkLed);
  timer0_start();
  sei();
  while (1)
  {
  }

  return 0;
}