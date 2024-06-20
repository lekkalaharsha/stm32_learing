/*
 * adc.h
 *
 *  Created on: Jun 20, 2024
 *      Author: Harsha Vardhan
 */


#ifndef INC_ADC_H_
#define INC_ADC_H_

#include "stm32f103xb.h"
#include <stdint.h>
#include "stm32f1xx.h"
void pa0_adc_init(void);
uint32_t adc_read(void);
void start_conversion(void);

#endif /* INC_ADC_H_ */
