/*
 * sytmclk.c
 *
 *  Created on: Jun 20, 2024
 *      Author: Harsha Vardhan
 */

#include "stm32f103xb.h"

#define SYSTICK_LOAD_VAL 16000 // Assuming a clock of 16 MHz for 1ms delay
#define CTRL_ENABLE (1U << 0)
#define CTRL_CLKSRC (1U << 2)
#define CTRL_COUNTFLAG (1U << 16)

void systickDelayMs(uint16_t n) {
    for (uint16_t i = 0; i < n; i++) {
        /* Configure SysTick */
        SysTick->LOAD = SYSTICK_LOAD_VAL - 1; // Set reload register (16000-1 for 1ms delay)
        SysTick->VAL = 0; // Clear current value register
        SysTick->CTRL = CTRL_ENABLE | CTRL_CLKSRC; // Enable SysTick with processor clock

        /* Wait until the COUNTFLAG is set */
        while ((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {
            // Wait for the flag to be set, which indicates timer has counted to 0
        }

        /* Disable SysTick to stop the timer */
        SysTick->CTRL = 0;
    }
}
