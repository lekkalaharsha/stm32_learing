#include "stm32f103xb.h"
#include "stm32f1xx.h"

#define USART2EN   (1U<<17)
#define GPIOAEN  (1U<<1)
#define SYS_FERQ   16000000
#define APB1_CLK    SYS_FERQ
#define UART_BAUDRATE   115200  
#define CR1_TE         (1U<<3)
#define CR1_UE     (1U<<13)
#define SR_TXE  (1U<<7)
static void  uart_set_baudrate(USART_TypeDef *USARTx,uint32_t periphCLK,uint32_t BaudRate);
static uint16_t compute_uart_bd(uint32_t PeriphCLK,uint32_t BaudRate);

void uar2_tx_init(void);
void uart2_write(int ch);

int main(){
	uar2_tx_init();
	
	while (1)
	{
	 uart2_write("y");
	
	}
}

void uar2_tx_init(void){
	/* .......configure  uart gpio pin.............*/
	/*Enable clock access to gpioa*/
	RCC->APB2ENR |= GPIOAEN;
	/*Set PA2 mode to alternate function mode*/
	GPIOA->CRL &=~(1U<<8);
	GPIOA->CRL |=(1U<<9);

	/*Set PA2 alternate function type to UART_TX */
	GPIOA->ODR |= (1U<<2);
	AFIO->MAPR &=~(1U<<3);
	/*.........configure uart module........*/
	/*Enable clock access to uart2*/
	RCC->APB1ENR |=USART2EN;
	
		/*configure baudrate*/
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);
	/*configure the transfer direction*/
	USART2->CR1 = CR1_TE;
	/*Enable usrt  module*/
	USART2->CR1 |= CR1_UE;

}

void uart2_write(int ch){
	/*Make sure the transmit data register is empty*/
	/*write to transmit data register*/
	while (!(USART2->SR & SR_TXE)){}

	USART2->DR (ch & 0&FF);
}
static void  uart_set_baudrate(USART_TypeDef *USARTx,uint32_t periphCLK,uint32_t BaudRate){
	USARTx->BRR compute_uart_bd(periphCLK,BaudRate);

}


static uint16_t compute_uart_bd(uint32_t PeriphCLK,uint32_t BaudRate){
	return ((PeriphCLK + (BaudRate/2U))/BaudRate);

}
