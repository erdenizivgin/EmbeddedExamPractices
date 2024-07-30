#include <avr/io.h>
#include "stdbool.h"
#include <avr/interrupt.h>
#include "serialmonitor.h"
#define MYUBRR F_CPU / 16 / BAUD - 1

void USART_Init(baud_rate_t br)
{
    uint16_t ubbr = F_CPU / 16 / br - 1;
    // Set baud rate
    UBRR0H = (ubbr >> 8);
    UBRR0L = ubbr;

    // Enable receiver, receiver interrupt and transmitter
    UCSR0B =  (1 << RXEN0) | (1 << TXEN0);

    // Set frame format: 8 data bits, 1 stop bit
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void USART_Transmit(unsigned char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (1 << UDRE0)))
        ;

    // Put data into buffer, sends the data
    UDR0 = data;
}

unsigned char USART_Receive(void)
{
    // Wait for data to be received
    while (!(UCSR0A & (1 << RXC0)))
        ;

    // Get and return received data from buffer
    return UDR0;
}

void USART_SendString(const char *str)
{
    while (*str)
    {
        USART_Transmit(*str++);
    }
}
