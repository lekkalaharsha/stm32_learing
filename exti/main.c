#include "exit.h"
#include "string.h"
#include "stdio.h"

static void exit_callback(void);

int main() {
	pc13_exit_init();
    while (1) {
         // Initialize EXTI for PC13 (assuming this function exists in your exit.h file)
    }
    return 0;
}

static void exit_callback(void) {
    printf("hii");
}

void EXTI15_10_IRQHandler(void) {
    if (EXTI->PR & EXTI_PR_PR13) { // Check if EXTI line 13 caused the interrupt
        EXTI->PR = EXTI_PR_PR13; // Clear the interrupt flag
        exit_callback(); // Call your exit_callback function
    }
}
