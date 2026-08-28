#ifndef GPIO_H
#define GPIO_H


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

void Clock_Init ( gpio_reg_map* gpiox );
void GPIO_Init ( gpio_reg_map* gpiox , GPIO_Config* obj );
void GPIO_Write ( gpio_reg_map* gpiox , uint8_t pin , uint8_t state );
void GPIO_Toggle ( gpio_reg_map* gpiox , uint8_t pin );
uint8_t GPIO_Read (gpio_reg_map* gpiox , uint8_t pin );
//void GPIO_SetPull ( gpio_reg_map* gpiox , uint8_t pin , uint8_t pull );
//void GPIO_SetOutput_Type( gpio_reg_map* gpiox , uint8_t pin , uint8_t type );
//void GPIO_SetOutput_Speed ( gpio_reg_map* gpiox , uint8_t pin , uint8_t speed );
//void GPIO_SetAF ( gpio_reg_map* gpiox, uint8_t pin , uint8_t af );



#endif
