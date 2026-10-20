#ifndef GPIO_H
#define GPIO_H
#include<stdint.h>

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



void GPIO_Init ( gpio_reg_map* gpiox , GPIO_Config* obj );/*Here first element is which GPIO Peripheral you are going to initialize..EX:GPIOA,GPIOB.....
second is the structure object that how you are going to configure the GPIO peripheral.... see GPIO_Config {} structure to know more */

void GPIO_Write ( gpio_reg_map* gpiox , uint8_t pin , uint8_t state );/*Here pin represents the pin number of the peripheral and state represents whether you want your output as  HIGH or LOW.  */

void GPIO_Toggle ( gpio_reg_map* gpiox , uint8_t pin );/*This function helps you to toggle the output once for every time this function is being called by you.  */

uint8_t GPIO_Read (gpio_reg_map* gpiox , uint8_t pin );/*Use this function to read the GPIO port . This will return 1 if it is HIGH,0 if it is LOW. */


#endif
