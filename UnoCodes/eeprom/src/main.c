#include "avr/io.h"
#include <util/delay.h>
#include "led.h"
#include "serialmonitor.h"
#include "eeprom.h"

#define EEPROM_ADDRESS 0x010
#define BUFFER_SIZE 10


int main(void)
{
  char data = '0';
  USART_Init(BAUD_RATE_9600);

  while (1)
  {
    _delay_ms(500);
    // write the data variable to memory address EEPROM_ADDRESS
    eeprom_write(EEPROM_ADDRESS, data);
    
    // read the data variable from address EEPROM_ADDRESS
    data = eeprom_read(EEPROM_ADDRESS);
    

    // send the data via UART to debug
    USART_Transmit((unsigned char)data);
    data++;
  }

  return 0;
}


