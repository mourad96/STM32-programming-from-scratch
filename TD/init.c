#include <stdint.h>
#include "memfuncs.h"

extern uint8_t _start_bss,_end_bss,_sfvector_table_lma,_startcopy_vma,_endcopy_vma;
extern uint8_t _data_begin,_data_end,text_end,_sidata,rodata_end,rodata_begin ;

void init_bss()
{
   memset(&_start_bss, 0, &_end_bss - &_start_bss);
}

void copy_data()
{
   memcpy(&text_end,&_sidata,&_data_end - &_data_begin);
}

void copy_to_RAM()
{
   memcpy(&_sfvector_table_lma,&_startcopy_vma,(int)&_endcopy_vma );
}
