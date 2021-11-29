#include <stdint.h>
#include "led.h"
#include "stm32l475xx.h"


void led(enum state state)
{
   if(state == LED_OFF)
   {
      // configurer en entrée
    GPIOC->MODER &= ~ GPIO_MODER_MODE9;//PC9 est en entrée (= haute impédance), les deux LED sont éteintes.
    
   }
   else if (state == LED_YELLOW)
   {
      // sortie, état haut
      GPIOC->BSRR = GPIO_BSRR_BS9; //PC9 est en sortie à l'état haut, LED3 est allumée, LED4 est éteinte.
      GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0; 
   }
   else
   {
      // sorti, état bas 
     GPIOC->BSRR   = GPIO_BSRR_BR9;  //PC9 est en sortie à l'état bas, LED3 est éteinte, LED4 est allumée.
     GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
     //GPIOC->BRR = GPIO_BRR_BR9;
   }
}

void led_init()
{
   //activation du clock du GPIOB et GPIOC
   
  RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);//IO port B clock enabled et IO port C clock enabled
                                                            
   //PB14 en mode sortie
   GPIOB->MODER = (GPIOB->MODER & ~ GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;
   
}
void led_g_on()
{
  GPIOB->ODR |= GPIO_ODR_OD14;//PB14 is on
}
void led_g_off()
{
   GPIOB->ODR &= ~GPIO_ODR_OD14;//PB14 is off
}
