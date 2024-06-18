
#include<stdio.h>
#include "uart.h"

 
int main(void) {

	uart2_tx_init();
    while (1) {
        printf("HELLO FROM .......\n\r"); // Corrected function call argument type
    }
    return 0;
}
