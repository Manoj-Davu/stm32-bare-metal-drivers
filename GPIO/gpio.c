#include "gpio.h"
#include<stdint.h>

void Clock_Init ( gpio_reg_map* gpiox )
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
