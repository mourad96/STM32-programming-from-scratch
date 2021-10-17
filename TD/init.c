#include <stdint.h>
#include "memfuncs.h"

uint8_t _start_bss,_end_bss;

void init_bss()
{
   memset(&_start_bss, 0, &_end_bss - &_start_bss);
}
