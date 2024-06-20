
#include<stdio.h>
#include "uart.h"
#include "adc.h"

uint32_t sensor_value;
int main(void) {
    pa0_adc_init();



	uart2_tx_init();
    while (1) {
    	start_conversion();

        sensor_value = adc_read();
        printf("%d",(int)sensor_value);
        


    }
    return 0;
}
