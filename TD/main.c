#include <stdint.h>
#include "led.h"

int fib(int n)
{
    if(n==0)
    {
        return 0;
    }
    else if (n==1)
    {
        return 1;
    }
    else
    {
        return fib(n-2) + fib(n-1);
    }
}
int main()
{
    led_init();
    while (1)
    {
        led_g_on();
      /* for (int i=0; i<1000; i++)//delay
       {
           asm volatile("nop");
       }*/
        led_g_off();
        for (int i=0; i<1000; i++)//delay
       {
           asm volatile("nop");
       }
    }

    return 0;
}