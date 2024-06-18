#include "uart.h"


// Definitions
#define USART2EN        (1U<<17)
#define GPIOAEN         (1U<<2)     // Corrected GPIOAEN value (shifted bit 2)
#define SYS_FREQ        8000000    // Corrected spelling from SYS_FERQ to SYS_FREQ
#define APB1_CLK        SYS_FREQ
#define UART_BAUDRATE   115200
#define CR1_TE          (1U<<3)
#define CR1_UE          (1U<<13)
#define SR_TXE          (1U<<7)
// Function prototypes
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphCLK, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphCLK, uint32_t BaudRate);

void uart2_tx_init(void);
void uart2_write(int ch);


int __io_putchar(int ch){
	uart2_write(ch);
	return ch;
}


void uart2_tx_init(void) {
    // Configure UART GPIO pin
    // Enable clock access to GPIOA
    RCC->APB2ENR |= GPIOAEN;

    // Set PA2 mode to alternate function output Push-Pull (50 MHz)
    GPIOA->CRL &= ~(0xF << 8);  // Clear PA2 bits
    GPIOA->CRL |= (0xB << 8);   // Set PA2 to Alternate Function Output Push-Pull

    // Enable clock access to USART2
    RCC->APB1ENR |= USART2EN;

    // Configure baud rate
    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    // Configure the transfer direction (transmit enable)
    USART2->CR1 = CR1_TE;

    // Enable USART module
    USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch) {
    // Wait until the transmit data register is empty
    while (!(USART2->SR & SR_TXE)) {}

    // Write to transmit data register
    USART2->DR = (ch);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphCLK, uint32_t BaudRate) {
    USARTx->BRR = compute_uart_bd(periphCLK, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphCLK, uint32_t BaudRate) {
    return ((PeriphCLK + (BaudRate / 2U)) / BaudRate);
}
