MEMORY
{
  flash(rx) : ORIGIN = 0x08000000, LENGTH = 1M
  sram1(wx) : ORIGIN = 0x20000000, LENGTH = 96K
  sram2(wx) : ORIGIN = 0x10000000, LENGTH = 32K
}
_stack = ORIGIN(sram2) + LENGTH(sram2);
ENTRY(_start)
_sfvector_table_lma = LOADADDR(.vector_table);
_startcopy_vma = ADDR(.vector_table);
_endcopy_vma = SIZEOF(.vector_table) + SIZEOF(.text) +SIZEOF(.data);

SECTIONS
{
  /*programme*/
  .vector_flash :
  {
    *(.vector_flash)
  } > flash

  .boot : {
    /* TODO */
    vector_flash.o(.text)
    memfuncs.o(.text)
    init.o(.text)
    ctr0.o(.text)
  } > flash

    /*constantes ici*/
  .rodata : {
    rodata_begin = .;
    *(.rodata)
    rodata_end = .;
  }>flash

  .vector_table : {
    *(.vector_table)
  } >sram1 AT> flash

  .text : {
    *(.text)
    text_end = .;
  }>sram1 AT> flash


  /*data ici*/
  _sidata = LOADADDR(.data);
  .data : {
    _data_begin = .;
    *(.data)
    _data_end = .;
  }>sram1 AT> flash

  /*données non initialiées*/
  _start_bss= .;
  .bss : {
    *(.bss)*(COMMON)
  }>sram1
  _end_bss= .;
}


