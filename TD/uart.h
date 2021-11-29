#ifndef UART_H
#define UART

#include <stdint.h>
#include "matrix.h"

extern volatile uint8_t trame[8*8*3];

void uart_init(int baudrate);
void uart_putchar(uint8_t c);
uint8_t uart_getchar(void);
void uart_puts(const char *s);
void uart_gets(char *s, uint16_t size);

#endif