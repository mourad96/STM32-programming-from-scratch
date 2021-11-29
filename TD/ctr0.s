.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

.thumb_func
_start:
    //ldr sp, = _stack
   // bl  copy_data
    bl  copy_to_RAM
    bl  init_bss
    bl  main
_exit:
    b _exit
