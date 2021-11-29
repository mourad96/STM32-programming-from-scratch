PREFIX = arm-none-eabi-
CC     = $(PREFIX)gcc
AS     = $(PREFIX)as
GDB    = $(PREFIX)gdb
INC    = -I CMSIS/Device/ST/STM32L4xx/Include -I CMSIS/Include
# compilation
CFLAGS       = -g -O1 -ffreestanding  $(INC)
TARGET_ARCH  = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
# asm
ASFLAGS      = -g
TARGET_MACH  = $(TARGET_ARCH)
# link
LDFLAGS      = -g -lc -nostdlib -T ld_ram.lds 


OBJ2 = clocks.o 
OBJS = main.o ctr0.o init.o memfuncs.o led.o uart.o matrix.o image.o irq.o buttons.o timer.o vector_flash.o
EXE  = main.exe



$(EXE): $(OBJS) $(OBJ2)
	$(CC) $(LDFLAGS) $^ -o $@

startjlinkgdb:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: $(EXE)
	$(GDB) $<

Jlink:
	JLinkExe -device STM32L475VG -if SWD -autoconnect 1 -speed auto

image.o:
	$(PREFIX)objcopy -I binary -O elf32-littlearm -B arm image.raw image.o

clean:
	rm -f $(EXE)
	rm -f $(OBJS)
