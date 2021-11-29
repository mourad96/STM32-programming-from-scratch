#include <stdint.h>
#include "stm32l475xx.h"
#include "buttons.h"

uint8_t button_flag =0;
void button_init()
{
    //active l'horloge du port C
    RCC->AHB2ENR|= RCC_AHB2ENR_GPIOCEN;
    RCC->APB2ENR|= RCC_APB2ENR_SYSCFGEN;
    //PC13 en GPIO et en entrée
    GPIOC->MODER &=~ GPIO_MODER_MODE13_Msk;
    //PC13 comme source d'IRQ pour EXTI13
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] &~ SYSCFG_EXTICR4_EXTI13_Msk ) | SYSCFG_EXTICR4_EXTI13_PC ;
    //EXTI configuraion
    EXTI->IMR1  |= EXTI_IMR1_IM13;
    EXTI->RTSR1 |= EXTI_RTSR1_RT13;
    EXTI->FTSR1 &=~ EXTI_FTSR1_FT13;
   // NVIC_EnableIRQ(EXTI4_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
    //activation du clock du GPIOB et GPIOC
   
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);//IO port B clock enabled et IO port C clock enabled
                                                            
   //PB14 en mode sortie
   GPIOB->MODER = (GPIOB->MODER & ~ GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;
   button_flag = 0;
   
}

/*void EXTI4_IRQHandler()
{


}*/
void EXTI15_10_IRQHandler()
{
  //clear flag
  EXTI->PR1 |= EXTI_PR1_PIF13;
  //appui sur le bouton poussoir B2 
  if (button_flag == 0){
    button_flag =1;
  }
  else{
    button_flag =0;
  }
}