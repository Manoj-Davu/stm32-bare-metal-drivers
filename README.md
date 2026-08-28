# STM32 Bare-Metal Drivers

A collection of peripheral drivers developed from scratch for STM32 microcontrollers using direct register-level programming without STM32 HAL.

## Drivers

### GPIO

* RCC clock enable
* GPIO configuration using `GPIO_Config`
* Input / Output / Alternate Function / Analog modes
* Pull-up / Pull-down configuration
* Push-pull / Open-drain configuration
* Output speed configuration
* Alternate Function configuration
* GPIO Read / Write / Toggle
* Tested on STM32F401CCU6 hardware

## Development Approach

The drivers are implemented using:

* C
* Memory-mapped peripheral registers
* Bit manipulation
* Register mapping using structures
* Configuration structures

More peripheral drivers will be added as they are implemented and tested on hardware.
