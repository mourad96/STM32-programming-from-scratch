#include "stm32l475xx.h"



void flash_Handler(void){__disable_irq();while(1);};



extern uint32_t _stack;
extern void _start(void);


void *__attribute__((section (".vector_flash")))vector_flash[] = {
    // Stack and Reset Handler
    &_stack,            /* Top of stack */
    _start,       /* Reset handler */

    // ARM internal exceptions
    flash_Handler,  /* NMI handler */
    flash_Handler,  /* Hard Fault handler */
    flash_Handler,
    flash_Handler,
    flash_Handler,
    0,              /* Reserved */
    0,              /* Reserved */
    0,              /* Reserved */
    0,              /* Reserved */
    flash_Handler,  /* SVC handler */
    0,              /* Reserved */
    0,              /* Reserved */
    flash_Handler,  /* Pending SVC handler */
    flash_Handler,  /* SysTick hanlder */
    };
    
