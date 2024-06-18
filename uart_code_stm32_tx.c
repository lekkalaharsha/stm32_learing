#include <stdint.h>
#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include<stdio.h>
// Definitions
#define USART2EN        (1U << 17)
#define GPIOAEN         (1U << 2)
#define SYS_FREQ        8000000
#define APB1_CLK        SYS_FREQ
#define UART_BAUDRATE   115200
#define CR1_TE          (1U << 3)
#define CR1_UE          (1U << 13)
#define SR_TXE          (1U << 7)

// Function prototypes
static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphCLK, uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphCLK, uint32_t BaudRate);

void uart2_tx_init(void);
void uart2_write(int ch);

int __io_putchar(int ch) {
    uart2_write(ch);
    return ch;
}

int main(void) {
    uart2_tx_init();

    while (1) {
       // uart2_write('harsga\n');
        printf("HELLO FROM harsha.......\n\r");
          // Simple delay  // Simple delay
    }
}

void uart2_tx_init(void) {
    RCC->APB2ENR |= GPIOAEN;

    GPIOA->CRL &= ~(0xF << 8);  // Clear PA2 bits
    GPIOA->CRL |= (0xB << 8);   // Set PA2 to Alternate Function Output Push-Pull

    RCC->APB1ENR |= USART2EN;

    uart_set_baudrate(USART2, APB1_CLK, UART_BAUDRATE);

    USART2->CR1 = CR1_TE;
    USART2->CR1 |= CR1_UE;
}

void uart2_write(int ch) {
    while (!(USART2->SR & SR_TXE)) {}
    USART2->DR = (ch);  // Send only the lower 8 bits
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t periphCLK, uint32_t BaudRate) {
    USARTx->BRR = compute_uart_bd(periphCLK, BaudRate);
}

static uint16_t compute_uart_bd(uint32_t PeriphCLK, uint32_t BaudRate) {
    return ((PeriphCLK + (BaudRate / 2U)) / BaudRate);
}
