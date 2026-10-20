#include "gpio.h"
#include<stdint.h>

#define GPIOA_CLK 0
#define GPIOB_CLK 1
#define GPIOC_CLK 2
#define GPIOD_CLK 3
#define GPIOE_CLK 4
#define GPIOF_CLK 5
#define GPIOG_CLK 6
#define GPIOH_CLK 7

#define RCC (*(volatile uint32_t*)0x40023830UL)

#include <stdint.h>

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1
#define GPIO_AF 2
#define GPIO_ANALOG 3

#define GPIOA_BASE 0x40020000UL
#define GPIOB_BASE 0x40020400UL
#define GPIOC_BASE 0x40020800UL
#define GPIOD_BASE 0x40020c00UL
#define GPIOE_BASE 0x40021000UL
#define GPIOF_BASE 0x40021400UL
#define GPIOG_BASE 0x40021800UL
#define GPIOH_BASE 0x40021c00UL


typedef struct
{
volatile uint32_t  MODER;
volatile uint32_t  OTYPER;
volatile uint32_t  OSPEEDR;
volatile uint32_t  PUPDR;
volatile uint32_t  IDR;
volatile uint32_t  ODR;
volatile uint32_t  BSRR;
volatile uint32_t  LCKR;
volatile uint32_t  AFR[2];
}gpio_reg_map;

typedef struct
{
uint8_t pin;
uint8_t Mode;
uint8_t pull;
uint8_t speed;
uint8_t otype;
uint8_t af;
}GPIO_Config;



#define GPIOA ((gpio_reg_map*)GPIOA_BASE)
#define GPIOB ((gpio_reg_map*)GPIOB_BASE)
#define GPIOC ((gpio_reg_map*)GPIOC_BASE)
#define GPIOD ((gpio_reg_map*)GPIOD_BASE)
#define GPIOE ((gpio_reg_map*)GPIOE_BASE)
#define GPIOF ((gpio_reg_map*)GPIOF_BASE)
#define GPIOG ((gpio_reg_map*)GPIOG_BASE)
#define GPIOH ((gpio_reg_map*)GPIOH_BASE)

#define GPIO_PINHIGH 1
#define GPIO_PINLOW 0

#define NOPULL 0
#define PULLUP 1
#define PULLDOWN 2

#define PUSHPULL 0
#define OPENDRAIN 1

#define LOWSPEED 0
#define MEDIUMSPEED 1
#define HIGHSPEED 2
#define VERYHIGH 3



static void Clock_Init ( gpio_reg_map* gpiox )
{
if ( gpiox==GPIOA )
	RCC|=( 1U<<GPIOA_CLK );

else if ( gpiox == GPIOB )
	RCC|=( 1U<<GPIOB_CLK );

else if ( gpiox == GPIOC )
	RCC|=( 1U<<GPIOC_CLK );

else if ( gpiox == GPIOD )
	RCC|=( 1U << GPIOD_CLK );

else if ( gpiox == GPIOE )
	RCC|=( 1U << GPIOE_CLK );

else if ( gpiox == GPIOF )
	RCC|=( 1U << GPIOF_CLK );

else if ( gpiox == GPIOG )
	RCC|=( 1U << GPIOG_CLK );

else if ( gpiox == GPIOH )
	RCC|=( 1U << GPIOH_CLK );

}

void GPIO_Init ( gpio_reg_map* gpiox , GPIO_Config* obj )

{

Clock_Init(gpiox);

uint8_t bit=obj->pin*2;


gpiox->MODER&=~(3U <<bit);
gpiox->MODER|=(obj->Mode<<bit);

if ( obj->Mode == GPIO_AF )
{
uint8_t index = obj->pin/8;
uint8_t af_bit = (obj->pin%8)*4;

gpiox->AFR[index] &=~(0xFU << af_bit );
gpiox->AFR[index] |= (obj->af << af_bit );

}
gpiox->PUPDR &=~(3U << bit);
gpiox->PUPDR|= (obj->pull << bit );

if ( obj->otype == OPENDRAIN )
	gpiox->OTYPER|=(1U<<obj->pin);
else
	gpiox->OTYPER&=~(1U<<obj->pin);


gpiox->OSPEEDR&=~(3U<<bit);
gpiox->OSPEEDR |= (obj->speed << bit);



}


void GPIO_Write ( gpio_reg_map* gpiox , uint8_t pin ,uint8_t state )
{
if ( state == GPIO_PINHIGH )
	gpiox->BSRR=( 1U << pin );
else
	gpiox->BSRR=( 1U << (pin+16) );

}

void GPIO_Toggle( gpio_reg_map* gpiox , uint8_t pin )
{
if ( gpiox->ODR & (1U << pin) )
	gpiox->BSRR= ( 1U<< (pin+16) );
else
	gpiox->BSRR= ( 1U << pin );


}

uint8_t GPIO_Read ( gpio_reg_map* gpiox , uint8_t pin )
{
	return (gpiox->IDR & (1U << pin )) ? GPIO_PINHIGH : GPIO_PINLOW ;
}

/*void GPIO_SetPull ( gpio_reg_map* gpiox , uint8_t pin , uint8_t pull )
{

uint8_t bit =pin * 2 ;

}*/

/*void GPIO_SetOutput_Type ( gpio_reg_map* gpiox , uint8_t pin , uint8_t type )
{

}*/
/*void GPIO_SetOutput_Speed ( gpio_reg_map* gpiox , uint8_t pin , uint8_t speed )
{
uint8_t bit = pin*2 ;
}*/


/*void GPIO_SetAF ( gpio_reg_map* gpiox , uint8_t pin , uint8_t af )
{

}
*/
