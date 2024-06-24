/*
 * exit.c
 *
 *  Created on: Jun 24, 2024
 *      Author: Harsha Vardhan
 */
#include "exit.h"


void pc13_exit_init(void){
    /*disable global interrupts*/
    __disable_irq();
    /*enable clock accross for gpioc*/
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    /*SET PC13 AS INPUT*/
        // Configure PC13 as input with pull-up
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13); // Clear the MODE and CNF bits for PC13
    GPIOC->CRH |= (0x8 << GPIO_CRH_CNF13_Pos);         // Set CNF to 10 (input with pull-up/down)
    GPIOC->ODR |= GPIO_ODR_ODR13;      
    /*enable clock access for syscfg*/
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    /*select port 0for exit 13*/
    AFIO->EXTICR[3] &=~(AFIO_EXTICR4_EXTI13);
    AFIO->EXTICR[3] |= AFIO_EXTICR4_EXTI13_PC; 

    /*unmask exit13*/
    EXTI->IMR |= EXTI_IMR_MR13;
    /*select filing edge trigger*/
    EXTI->FTSR |= EXTI_FTSR_TR13;
    /*enable exit line in nvic */
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    /*enable global interrupts*/
    __enable_irq();
    }
