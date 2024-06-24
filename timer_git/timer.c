/*
 * timer.c
 *
 *  Created on: Jun 21, 2024
 *      Author: Harsha Vardhan
 */

#include"timer.h"


#define TIM1EN      (1U<<11)


void time1_1hz_init(void){
    /*ENABLE CLOCK ACCESS TO TIM2*/
    RCC->APB2ENR |= TIM1EN;
    /*SET PRESCALER VALUE*/
    TIM1->PSC =1600-1;

    /*SET AUTO-RELOAD VALUE*/
    TIM1->ARR = 10000 -1 ;

    /*CLEAR COUNTER*/
    TIM1->CNT =0;

    /*ENABLE TIMER*/
    TIM1->CR1 |= (1U<<0);

}
  // Include the header file for your specific STM32 series

void time1_pa8_output_compare(void) {

    /* Enable clock access to GPIOA */
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    /* Set PA8 mode to alternate function */
    GPIOA->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_CNF8); // Clear the relevant bits
    GPIOA->CRH |= (0x2 << GPIO_CRH_MODE8_Pos) | (0x2 << GPIO_CRH_CNF8_Pos); 
    // MODE8: 10 (Output mode, max speed 2 MHz)
    // CNF8: 10 (Alternate function output Push-pull)

    /* Enable clock access to TIM1 */
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    /* Set prescaler value */
    TIM1->PSC = 1600 - 1;  // Prescaler of 1599 to get 10 kHz

    /* Set auto-reload value */
    TIM1->ARR = 10000 - 1; // Auto-reload value of 9999 for 1 second period

    /* Set output compare toggle mode for channel 1 */
    TIM1->CCMR1 &= ~(TIM_CCMR1_OC1M); // Clear OC1M bits
    TIM1->CCMR1 |= (0x3 << TIM_CCMR1_OC1M_Pos);  // Set OC1M to 011 for toggle mode

    /* Enable TIM1 CH1 in compare mode */
    TIM1->CCER |= TIM_CCER_CC1E; // Enable capture/compare for channel 1

    /* Clear counter */
    TIM1->CNT = 0;

    /* Enable timer */
    TIM1->CR1 |= TIM_CR1_CEN; // Start the timer
}
