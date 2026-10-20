#ifndef GPIO_H
#define GPIO_H



void GPIO_Init ( gpio_reg_map* gpiox , GPIO_Config* obj );/*Here first element is which GPIO Peripheral you are going to initialize..EX:GPIOA,GPIOB.....
second is the structure object that how you are going to configure the GPIO peripheral.... see GPIO_Config {} structure to know more */

void GPIO_Write ( gpio_reg_map* gpiox , uint8_t pin , uint8_t state );/*Here pin represents the pin number of the peripheral and state represents whether you want your output as  HIGH or LOW.  */

void GPIO_Toggle ( gpio_reg_map* gpiox , uint8_t pin );/*This function helps you to toggle the output once for every time this function is being called by you.  */

uint8_t GPIO_Read (gpio_reg_map* gpiox , uint8_t pin );/*Use this function to read the GPIO port . This will return 1 if it is HIGH,0 if it is LOW. */


#endif
