#include <stdint.h>
#include "led.h"

#define RCC_BASE 0x40021000
#define RCC_AHB2ENR *((volatile uint32_t*)(RCC_BASE+0x4C))

#define GPIOB_BASE 0x48000400 
#define GPIOB_MODER *((volatile uint32_t*)(GPIOB_BASE+0x00))
#define GPIOx_ODR   *((volatile uint32_t*)(GPIOB_BASE+0x14))

void led_init()
{
   //activation du clock du GPIOB
   RCC_AHB2ENR =(RCC_AHB2ENR & ~(0x1<<1U))| (0x1<<1U);  //IO port B clock enabled
   //PB14 en mode sortie
   GPIOB_MODER =(GPIOB_MODER & ~(0x3<<28U))| (0x1<<28U);
}
void led_g_on()
{
  GPIOx_ODR  =(GPIOx_ODR & ~(0x1<<14U))| (0x1<<14U);//PB14 is on
}
void led_g_off()
{
   GPIOx_ODR  =(GPIOx_ODR & ~(0x1<<14U));//PB14 is off
}