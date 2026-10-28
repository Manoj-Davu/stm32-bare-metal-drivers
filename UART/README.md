# STM32 Bare-Metal UART Driver

A register-level UART driver written from scratch in Embedded C for the **STM32F401CCU6 (ARM Cortex-M4)**, without relying on STM32 HAL or other high-level peripheral libraries.

This project is part of my journey into bare-metal firmware development, where I'm learning to configure and control microcontroller peripherals by working directly with hardware registers.

## Current Features

- Direct USART register-level configuration.
- UART initialization and deinitialization.
- Baud-rate configuration.
- Data transmission using polling.
- Data reception using polling.
- String transmission.
- Support for multiple USART/UART peripherals through a common driver interface.
- Tested on physical STM32 hardware.

## How It Works

The driver configures the selected UART peripheral by accessing its registers directly.

- **Transmission:** Polls the TXE (Transmit Data Register Empty) flag before writing data.
- **Reception:** Polls the RXNE (Read Data Register Not Empty) flag before reading received data.

This implementation uses blocking, polling-based communication. The CPU waits for the relevant status flag instead of performing other tasks while the operation is in progress.

## How to Use the Driver

### 1. Add the Driver Files

Include the driver source and header files in your project:

```text
your_project/
├── src/
│   └── main.c
├── uart.c
├── uart.h
├── startup.s
└── linker.ld
```

Adjust the file locations according to your project structure.

### 2. Include the Header

Include the UART driver header in your application:

```c
#include <stdint.h>
#include "uart.h"
```

### 3. Configure and Initialize UART

Create a UART configuration using the configuration structure and enum values provided by `uart.h`.

For example, configure USART1 for 9600 baud, 8 data bits, no parity, and one stop bit.

> **Important:** Replace the illustrative configuration fields below with the exact field names and enum values defined in your `uart.h`.

```c
UART_Config config = {
    /* Select USART1 */
    /* Baud rate: 9600 */
    /* Word length: 8 bits */
    /* Parity: None */
    /* Stop bits: 1 */
};

UART_Handle uart;

UART_Init(&uart, &config);
```

The actual initialization call and parameter order must match your driver's function declaration.

### 4. Transmit Data

Once the UART peripheral is initialized, use the driver's transmission functions.

**Transmit a string:**

```c
UART_TransmitString(&uart, "Hello from STM32!\r\n");
```

**Transmit a single byte:**

```c
UART_TransmitByte(&uart, 'A');
```

These calls illustrate the intended usage. Verify their exact argument types against your implementation.

### 5. Receive Data

The driver can receive data by polling the UART status register.

Illustrative example:

```c
uint8_t received_data;

UART_ReceiveByte(&uart, &received_data);
```

The receive operation blocks until data becomes available, assuming the implementation has no timeout.

## Hardware Connections

For testing USART1 on the STM32F401CCU6 with an FT232RL USB-to-TTL converter:

| STM32F401CCU6 | FT232RL |
|---|---|
| PA9 (USART1_TX) | RX |
| PA10 (USART1_RX) | TX |
| GND | GND |

**Important:** Connect the adapter's TX to the microcontroller's RX, and the adapter's RX to the microcontroller's TX. Ensure the adapter's signal voltage is compatible with the STM32.

## Testing on Linux

I used Ubuntu Linux and a USB-to-TTL converter to test serial communication.

Install picocom if necessary:

```bash
sudo apt install picocom
```

Open the serial terminal at 9600 baud:

```bash
picocom -b 9600 /dev/ttyUSB0
```

The device may appear under a different name, such as `/dev/ttyUSB1`.

To exit picocom, press `Ctrl+A`, followed by `Ctrl+X`.

## Hardware & Tools

- **Microcontroller:** STM32F401CCU6
- **Core:** ARM Cortex-M4
- **Language:** Embedded C
- **Development environment:** Ubuntu Linux
- **Compiler:** ARM GCC
- **Debugging:** OpenOCD and GDB
- **Serial interface:** FT232RL USB-to-TTL converter

## Current Limitations

This is a functional, hardware-tested polling driver, but it is **not yet production-ready**.

Current limitations include:

- Blocking transmit and receive operations.
- No configurable timeout for polling operations yet.
- Error handling and recovery need further development.
- No interrupt-driven communication.
- No DMA-based data transfer.
- Additional validation and testing are required for more demanding applications.

## Future Improvements

My goal is to evolve this driver into a more robust, production-oriented UART driver.

- [ ] Add timeout handling to prevent indefinite blocking.
- [ ] Implement UART error detection and handling.
- [ ] Improve initialization validation and failure reporting.
- [ ] Add interrupt-driven transmission and reception.
- [ ] Implement DMA-based communication.
- [ ] Introduce receive buffers and ring-buffer support.
- [ ] Improve concurrency and state management.
- [ ] Test edge cases, invalid configurations, and communication failures.
- [ ] Add comprehensive documentation and test cases.

## Learning Objectives

Through this project, I'm developing a deeper understanding of:

- Memory-mapped peripheral registers.
- USART control and status registers.
- Baud-rate generation.
- Blocking I/O and polling.
- Embedded C and hardware-level debugging.
- The process of evolving a basic driver into more robust firmware.

## Project Status

**Current stage:** Polling-based UART driver, implemented and tested on physical hardware.

**Next stage:** Improving error handling, timeout management, and communication reliability before introducing interrupt-driven and DMA-based operation.

This project is actively evolving as I continue learning and implementing embedded firmware from the register level up.

---

*Built from scratch as part of my hands-on journey into bare-metal embedded systems and firmware engineering.*
