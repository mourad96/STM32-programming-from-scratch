.syntax unified
.arch armv7-m
.cpu cortex-m4
.thumb

.global _start

_start:
    ldr sp, = _stack
   # bl  init_bss
    bl  main
_exit:
    b _exit
