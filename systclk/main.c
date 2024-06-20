#include "stm32f103xb.h"
#include"systmclk.h"
#include "stm32f1xx.h"
#define GPICEN  (1UL << 4U)
#define PIN13   13U
#define LEDPIN  (1UL << PIN13)
int main(void){
	RCC->APB2ENR |= GPICEN;
	GPIOC->CRH |= (1U<<20);
	while (1)
	{
		/* code */
        // 3. TOGGLE GPIOC PIN 13
        GPIOC->BSRR = (LEDPIN<<16);
        systickDelayMs(1000);// Delay
        GPIOC->BSRR = LEDPIN;
        systickDelayMs(1000);  // Delay
	}
}
