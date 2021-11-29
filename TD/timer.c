#include <stdint.h>
#include "stm32l475xx.h"
#include "timer.h"
#include "irq.h"

volatile uint8_t count_tim2 = 0;
void timer_init(int max_us)
{
    //activation de l'horloge du timer TIM2
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
    TIM2->CR1 &= ~(TIM_CR1_CEN);
    TIM2->SR = 0;
    TIM2->CNT = 0;
    TIM2->PSC = 79; //1MHZ
    TIM2->ARR = max_us -1;
    //mode compteur (upcounter)
    TIM2->CR1 &=~ TIM_CR1_DIR ;
    // Auto-reload preload enable
    TIM2->CR1 |= TIM_CR1_ARPE ;
    // UEV enabled
    TIM2->CR1 &=~ TIM_CR1_UDIS;
    TIM2->CR1 &=~ TIM_CR1_URS;
    // Re-initialize the counter and generates an update of the registers
    TIM2->EGR |= TIM_EGR_UG;
    //period in milsec= 1 000 000 * (PSC+1)*(ARR+1) / TmerClockFreq  
    
    //update unterrupt enable
    TIM2->DIER |= TIM_DIER_UIE;
    //enable counter
    TIM2->CR1 |= TIM_CR1_CEN;
    //enable interrupt handler
    NVIC_EnableIRQ(TIM2_IRQn);
    
}

void TIM2_IRQHandler()
{
    //clear flag
    TIM2->SR &=~ TIM_SR_UIF;
    //toggle led2
    //GPIOB->ODR ^= GPIO_ODR_OD14;
    //
    if (count_tim2 >= 60 )
    {
        count_tim2 = 0;
    }
    
    count_tim2++;
 
}