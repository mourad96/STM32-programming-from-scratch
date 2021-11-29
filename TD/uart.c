#include <stdint.h>
#include "stm32l475xx.h"
#include "uart.h"
#include "irq.h"
#include "matrix.h"

void uart_init(int baudrate)
{
    // activation du clock du PORTB
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    //activation du clock du USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    //Alternate Function mode sur PB6 et PB7 
    GPIOB->MODER = (GPIOB->MODER & ~ (GPIO_MODER_MODE7_Msk | GPIO_MODER_MODE6_Msk ) ) | (GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1);
    //AF7= 0111
    GPIOB->AFR[0] = (GPIOB->AFR[0] & ~(GPIO_AFRL_AFSEL6_Msk | GPIO_AFRL_AFSEL7_Msk)) |( (7U<< GPIO_AFRL_AFSEL7_Pos) | (7U<< GPIO_AFRL_AFSEL6_Pos));
    //PCLK selecter pour l'horloge de USART1 
    RCC->CCIPR = (RCC->CCIPR & ~RCC_CCIPR_USART1SEL_Msk);
    //reset du USART1
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &=~RCC_APB2RSTR_USART1RST;
    // désactivation de l'usart1 et sa config
    //1 Start bit, 8 data bits M1=00;
    //Oversampling by 16
    USART1->CR1 = 0;
    USART1->CR1 &= ~ (USART_CR1_M0_Msk | USART_CR1_M1_Msk);
    USART1->CR1 &= ~ (USART_CR1_OVER8_Msk);
    USART1->CR1 &= ~ (USART_CR1_PCE_Msk);
    // 00: 1 stop bit
    USART1->CR2 =0;
    USART1->CR3 =0;
    USART1->CR2 &= ~ (USART_CR2_STOP_Msk);
    //baudrate
    int usartDiv = 80000000/baudrate;   
    USART1->BRR = usartDiv;
    //UART interrupt 
    USART1->CR1 |= USART_CR1_RXNEIE ;
    //UART ERROR interrupt
    USART1->CR3 |= USART_CR3_EIE ;
    // activer l'uart,le recepteur et le transmetteur
    
    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE;
    USART1->CR1 |= USART_CR1_UE ;
    //interrupt enable
    NVIC_EnableIRQ(USART1_IRQn);

    int count_uart =0;
}


volatile uint8_t trame[8*8*3];

void USART1_IRQHandler()
{
    static int count_uart = 0;
    static uint8_t USART_ERROR_FLAG = 0;
    if ((USART1->ISR & USART_ISR_ORE_Msk) || (USART1->ISR & USART_ISR_FE))// Overrun error or  Framing error
    {
        USART1->ICR |= USART_ICR_ORECF;
        USART1->ICR |= USART_ICR_FECF;
        USART_ERROR_FLAG = 1;
    }
    
    uint8_t c = USART1->RDR;
    if ((USART_ERROR_FLAG == 1)&& (c != 0xFF))
    {
        //la trame courante est ignorée et qu'on se remette en attente de la prochaine trame.
    }
    else{
        if (c == 0xff || count_uart == 192 )
        {
            count_uart = 0;
            USART_ERROR_FLAG = 0;
        }
        else{
            trame[count_uart] = c;
            count_uart ++;
        }

    }
    
}

void uart_putchar(uint8_t c)
{
    while (!(USART1->ISR & USART_ISR_TXE_Msk))//attend que l'USART1 soit prêt à transmettre quelque chose
    {
    }
    
    USART1->TDR = c;

}

uint8_t uart_getchar()
{
    while (!(USART1->ISR & USART_ISR_RXNE_Msk))//attend que l'UART ait reçu un caractère 
    {

    }

    return USART1->RDR;
}

void uart_puts(const char *s)
{
    int i=0;
    while (s[i]!='\0')
    {
        uart_putchar(s[i]);
        i++;
    }
    uart_putchar('\0');
    uart_putchar('\n');
}

void uart_gets(char *s, uint16_t size)
{
    for(int i=0; i<=size; i++)
    {
        s[i]=uart_getchar();
    }
    
}