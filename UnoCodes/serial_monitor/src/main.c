#include "avr/io.h"
#include "stdbool.h"
#include <util/delay.h>
#include "serialmonitor.h"



int main(void)
{

 
  USART_Init(BAUD_RATE_9600);

  while (1)
  {
    unsigned char receive = USART_Receive();
    USART_Transmit(receive);

  }

  return 0;
}

