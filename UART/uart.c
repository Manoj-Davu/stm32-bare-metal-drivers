#include "uart.h"
#include<stddef.h>

#define RCC_APB1ENR (*(volatile uint32_t *)0x40023840)
#define RCC_APB2ENR (*(volatile uint32_t *)0x40023844)

#define USART6_BASE 0x40011400
#define USART1_BASE 0x40011000
#define USART2_BASE 0x40004400
#define UART4_BASE  0x40004C00
#define UART5_BASE  0x40005000


#define USART1 ((usart_reg_map *)USART1_BASE)
#define USART2 ((usart_reg_map *)USART2_BASE)
#define USART6 ((usart_reg_map *)USART6_BASE)
#define UART4 ((usart_reg_map *)UART4_BASE)
#define UART5 ((usart_reg_map *)UART5_BASE)




static int UART_EnableClock(UART_Port port)
{
	switch(port)
		{
			case UART_PORT_USART1:RCC_APB2ENR|=(1<<4);
						break;
			case UART_PORT_USART2:RCC_APB1ENR|=(1<<17);
						break;
			case UART_PORT_USART6:RCC_APB2ENR|=(1<<5);
						break;
			case UART_PORT_UART4:RCC_APB1ENR|=(1<<19);
						break;
			case UART_PORT_UART5:RCC_APB1ENR|=(1<<20);
						break;
			default:return 0;
		}
	return 1;
}


static usart_reg_map *UART_GetInstance(UART_Port port)
{
	switch(port)
		{
			case UART_PORT_USART1:return USART1;
			case UART_PORT_USART2:return USART2;
			case UART_PORT_USART6:return USART6;
			case UART_PORT_UART4:return UART4;
			case UART_PORT_UART5:return UART5;
			default:return NULL;
		}
}


static uint32_t UART_GetPeripheralClock(UART_Port port)
{
	switch(port)
		{
        		case UART_PORT_USART1:return 16000000U;
        		case UART_PORT_USART2:return 16000000U;
        		case UART_PORT_USART6:return 16000000U;
        		case UART_PORT_UART4:return 16000000U;
        		case UART_PORT_UART5:return 16000000U;
        		default:return 0;
		}

}


static uint16_t UART_CalculateBRR(uint32_t frequency, uint32_t baudrate)
{
    	if (frequency == 0U || baudrate == 0U)
        	return 0U;

    	if (baudrate > frequency)
        	return 0U;

    	uint32_t brr = (frequency + (baudrate / 2U)) / baudrate;

    	if (brr < 16U || brr > 65535U)
        	return 0U;

    	uint64_t target = (uint64_t)baudrate * brr;
    	uint64_t difference;

    	if (frequency >= target)
        	difference = (uint64_t)frequency - target;
    	else
        	difference = target - (uint64_t)frequency;

    	if (difference * 100U > target)
        	return 0U;

    	return (uint16_t)brr;
}

static uint8_t UART_CheckConfig(const UART_Config *config)
{
	if(!config)
		return 0;

	if(config->parity!=UART_NO_PARITY && config->parity!=UART_EVEN_PARITY && config->parity!=UART_ODD_PARITY)
		return 0;

	if(config->word_length!=UART_8BIT && config->word_length!=UART_9BIT)
		return 0;

	if(config->stop_bits!=UART_1STOPBIT && config->stop_bits!=UART_2STOPBIT)
		return 0;

	if(config->rx_enable!=UART_ENABLE && config->rx_enable!=UART_DISABLE)
		return 0;

	if(config->tx_enable!=UART_ENABLE && config->tx_enable!=UART_DISABLE)
		return 0;


	return 1;
}


int UART_Init(UART_Handle *handle, UART_Port port, const UART_Config *config)

{
	if(!handle || !config)
		return 0;

	handle->instance = NULL;

	usart_reg_map *instance=UART_GetInstance(port);
	if(!instance)
		return 0;

	if(!UART_CheckConfig(config))
		return 0;

	uint32_t brr= UART_CalculateBRR(UART_GetPeripheralClock(port),config->baud_rate);

	if(!brr)
		return 0;


	uint8_t clock_status=UART_EnableClock(port);
	if(!clock_status)
		return 0;
	instance->USART_CR1&=~(1<<13);
	instance->USART_CR1 &= ~(1U << 15);
	instance->USART_BRR=brr;

	if(config->rx_enable==UART_ENABLE)
		instance->USART_CR1|=(1<<2);
	else
		instance->USART_CR1&=~(1<<2);

	if(config->tx_enable==UART_ENABLE)
		instance->USART_CR1|=(1<<3);
	else
		instance->USART_CR1&=~(1<<3);

	if(config->word_length==UART_9BIT)
		instance->USART_CR1|=(1<<12);
	else
		instance->USART_CR1&=~(1<<12);

	switch(config->parity)
		{
			case UART_NO_PARITY:instance->USART_CR1&=~(1<<10);
			    		    instance->USART_CR1&=~(1<<9);
						break;
			case UART_EVEN_PARITY:instance->USART_CR1|=(1<<10);
		      	      		      instance->USART_CR1&=~(1<<9);
						break;
			case UART_ODD_PARITY:instance->USART_CR1|=(1<<10);
		     	     		     instance->USART_CR1|=(1<<9);
						break;
			default:return 0;
		}

	instance->USART_CR2 &= ~(3U << 12);
	if(config->stop_bits==UART_2STOPBIT)
		instance->USART_CR2|=(2<<12);

	instance->USART_CR2&=~(1<<11);
	instance->USART_CR1|=(1<<13);
	handle->instance=instance;
	handle->port=port;

	return 	1;
	}


int UART_TransmitByte(UART_Handle *handle, uint8_t data)
{
	if(!handle || !handle->instance)
		return 0;

	while(!(handle->instance->USART_SR&(1<<7))){}

	handle->instance->USART_DR=data;
	return 1;
}

int UART_ReceiveByte(UART_Handle *handle, uint8_t *data)
{
	if(!handle || !handle->instance || !data)
		return 0;

	while(!(handle->instance->USART_SR&(1<<5))){}

	*data=handle->instance->USART_DR;
	return 1;
}


int UART_TransmitString(UART_Handle *handle, const char *str)
{
	if(!handle || !handle->instance || !str)
		return 0;

	while(*str!='\0')
		{
			if(!UART_TransmitByte(handle,*str))
				return 0;
			str++;
		}
	return 1;
}

static int UART_DisableClock(UART_Port port)
{
	switch(port)
        	{
        		case UART_PORT_USART1:RCC_APB2ENR&=~(1<<4);
                           	     break;
        		case UART_PORT_USART2:RCC_APB1ENR&=~(1<<17);
                        	        break;
        		case UART_PORT_USART6:RCC_APB2ENR&=~(1<<5);
                        	        break;
        		case UART_PORT_UART4:RCC_APB1ENR&=~(1<<19);
                        	        break;
        		case UART_PORT_UART5:RCC_APB1ENR&=~(1<<20);
                        	        break;
       	 		default:return 0;
        	}
	return 1;
}


int UART_DeInit(UART_Handle *handle)
{

	if(!handle || !handle->instance)
		return 0;

	usart_reg_map *instance=UART_GetInstance(handle->port);
	if(!instance)
        	return 0;
	if (instance != handle->instance)
    		return 0;
	handle->instance->USART_CR1&=~(1U<<13);


	if(!UART_DisableClock(handle->port))
		return 0;

	handle->instance=NULL;
return 1;
}
