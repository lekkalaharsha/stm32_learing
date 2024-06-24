/*
 * exit.h
 *
 *  Created on: Jun 24, 2024
 *      Author: Harsha Vardhan
 */

#ifndef INC_EXIT_H_
#define INC_EXIT_H_
#include "stm32f103xb.h"
#include <stdint.h>
#include "stm32f1xx.h"

void pc13_exit_init(void);
#define LINE13      (1U<<13)


#endif /* INC_EXIT_H_ */
