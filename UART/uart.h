#ifndef UART_H
#define UART_H
#include<stdint.h>



typedef struct
{
volatile uint32_t USART_SR;  //0x00
volatile uint32_t USART_DR;  //0x04
volatile uint32_t USART_BRR; //0x08
volatile uint32_t USART_CR1; //0x0c
volatile uint32_t USART_CR2; //0x10
volatile uint32_t USART_CR3; //0x14
volatile uint32_t USART_GTPR;//0x18
}usart_reg_map;



typedef enum
{
UART_NO_PARITY,
UART_EVEN_PARITY,
UART_ODD_PARITY
}UART_Parity;

typedef enum
{
UART_8BIT,
UART_9BIT
}UART_WordLength;

typedef enum
{
UART_1STOPBIT,
UART_2STOPBIT
}UART_StopBit;

typedef enum
{
UART_ENABLE,
UART_DISABLE
}UART_State;

typedef struct
{
uint32_t baud_rate;
UART_Parity parity;
UART_WordLength word_length;
UART_StopBit  stop_bits;
UART_State  rx_enable;
UART_State  tx_enable;
}UART_Config;
typedef enum
{
    UART_PORT_USART1,
    UART_PORT_USART2,
    UART_PORT_USART6,
    UART_PORT_UART4,
    UART_PORT_UART5
} UART_Port;

typedef struct
{
    UART_Port port;
    usart_reg_map *instance;
} UART_Handle;






int UART_Init(UART_Handle *handle, UART_Port port, const UART_Config *config);
int UART_TransmitByte(UART_Handle *handle, uint8_t data);
int UART_ReceiveByte(UART_Handle *handle, uint8_t *data);
int UART_TransmitString(UART_Handle *handle, const char *str);
int UART_DeInit(UART_Handle *handle);

#endif
