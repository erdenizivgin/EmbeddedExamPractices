#include "avr/io.h"
#include <util/delay.h>

#define LEDPIN PB0
#define LEDPORT PORTB
#define LEDDDR DDRB

int main(void)
{

  LEDDDR |= (1 << LEDPIN);

  while (1)
  {
    LEDPORT ^= (1 << LEDPIN);
    _delay_ms(1000);
  }

  return 0;
}