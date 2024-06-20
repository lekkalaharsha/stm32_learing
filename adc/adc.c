#include "adc.h"

#define GPIOAEN (1U << 2)
#define ADC1EN (1U << 9) // Corrected to 9 based on STM32
#define ADC_CH1 1U
#define ADC_CH2 2U
#define ADC_CH3 3U
#define ADC_CH5 5U
#define ADC_SEQ_LEN_1 0x00
#define ADC_ADON (1U << 0)
#define ADC_SWST (1U << 22)
#define SR_ECO (1U << 1)

void pa0_adc_init(void) {
    /**** CONFIGURE THE ADC GPIO PIN ****/
    
    /* ENABLE CLOCK ACCESS TO GPIOA */
    RCC->APB2ENR |= GPIOAEN;
    
    /* SET THE MODE OF PA0 TO ANALOG */
    GPIOA->CRL &= ~(0xF << 0); // Clear PA0 bits
    
    /*** CONFIGURE THE ADC MODULE ***/
    
    /* ENABLE CLOCK ACCESS TO ADC */
    RCC->APB2ENR |= ADC1EN;
    
    /* Configure the sequence for channels 5, 2, 3 */
    ADC1->SQR3 = (ADC_CH5 << 0) | (ADC_CH2 << 5) | (ADC_CH3 << 10);
    ADC1->SQR1 = 2; // Sequence length 3 (actual length - 1)
    
    /* ENABLE ADC MODULE */
    ADC1->CR2 |= ADC_ADON;
}

void start_conversion(void) {
    /* Start ADC conversion */
    ADC1->CR2 |= ADC_SWST;
}

uint32_t adc_read(void) {
    /* Wait for conversion to be complete */
    while (!(ADC1->SR & SR_ECO)) {}
    
    /* Read converted result */
    return (ADC1->DR);
}
