#include "avr/io.h"
#include "avr/interrupt.h"
#include "stdbool.h"
#include <util/delay.h>
#include "serialmonitor.h"

volatile char message = 0;
volatile bool receiveFlag = false;
int main(void)
{

  USART_Init(BAUD_RATE_9600);
  sei();
  while (1)
  {
    while (!receiveFlag)
      ;

    USART_Transmit(message);
    receiveFlag = false;
  }

  return 0;
}

ISR(USART_RX_vect)
{
  message = UDR0;
  receiveFlag = true;
}
