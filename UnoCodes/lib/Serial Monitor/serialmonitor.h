#ifndef SERIALMONITOR_H_
#define SERIALMONITOR_H_

typedef enum baud_rate_e
{
    BAUD_RATE_2400 = 2400,
    BAUD_RATE_4800 = 4800,
    BAUD_RATE_9600 = 9600,
    BAUD_RATE_14400 = 14400,
    BAUD_RATE_15200 = 115200
} baud_rate_t;

/*PROTOTYPES *****************************************************************/
void USART_Init();
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);
void USART_SendString(const char *str);
#endif /* SERIALMONITOR_H_ */