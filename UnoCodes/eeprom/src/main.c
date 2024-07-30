#include "avr/io.h"
#include <stdio.h>
#include <util/delay.h>
#include "led.h"
#include "serialmonitor.h"
#include "eeprom.h"
#include "timer.h"

#define EEPROM_ADDRESS 0x010

int main(void)
{
  uint8_t data = 'a';
  //char buffer[128];
  USART_Init();
  FILE *fptr;
  fptr = fopen("C:\\C code\\EmbeddedExamPractices\\data.txt","w");

  while (1)
  {
    _delay_ms(1000);
    data++;
    // write the data variable to memory address 123
    eeprom_write(EEPROM_ADDRESS, data);
    //read the data variable from address 123
    data = eeprom_read(EEPROM_ADDRESS);
    // send the data via UART to debug
    //sprintf(buffer, "%u is read from eeprom\n", data);
    //USART_Transmit((unsigned char)data);
    fprintf(fptr,"%c\n",data);
  }
  fclose(fptr);
  return 0;
}
