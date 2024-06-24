#include "stm32f103xb.h"
#include "stm32f1xx.h"
#include "timer.h"
#define GPICEN  (1UL << 4U)
#define PIN13   13U
#define LEDPIN  (1UL << PIN13)
#define SR_UIF          (1U<<0)
int main(void){
	RCC->APB2ENR |= GPICEN;
	GPIOC->CRH |= (1U<<20);
	time1_1hz_init();
	while (1)
	{
		/* code */
        /*WAIT FOR UIF*/
		while (!(TIM1->SR & TIM_SR_UIF)){}
		/*CLEAR UIF*/
		TIM1->SR &=~SR_UIF;
		// 3. TOGGLE GPIOC PIN 13
        GPIOC->BSRR = (LEDPIN<<16);
        for (volatile int i = 0; i < 100000; ++i);  // Delay
        GPIOC->BSRR = LEDPIN;
        for (volatile int i = 0; i < 100000; ++i);  // Delay
	}
}
