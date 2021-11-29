#include <stdint.h>

#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
#include "timer.h"
#include "stm32l475xx.h"


int main()
{
    
    clocks_init();
    irq_init();
    led_init();
    button_init();
    matrix_init();
    uart_init(38400);
    timer_init(16);


    while (1)
    {
       if (count_tim2 == 60)
       {
           display_image((rgb_color*)trame);
       }
     // display_image(_binary_image_raw_start); 

    } 
    return 0;
}