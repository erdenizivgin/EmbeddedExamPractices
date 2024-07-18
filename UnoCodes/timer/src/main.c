#include "avr/io.h"
#include <util/delay.h>


#define LEDPIN PB5
#define LEDPORT PORTB
#define LEDDDR DDRB

int main(void)
{

  LEDDDR |= (1 << LEDPIN);

  while (1)
  {
    LEDPORT ^= (1 << LEDPIN);
    _delay_ms(200);
  }

  return 0;
}