PREFIX = arm-none-eabi-
CC     = $(PREFIX)gcc
AS     = $(PREFIX)as
GDB    = $(PREFIX)gdb

# compilation
CFLAGS       = -g -O1 -ffreestanding
TARGET_ARCH  = -mcpu=cortex-m4 -mthumb
# asm
ASFLAGS      = -g
TARGET_MACH  = $(TARGET_ARCH)
# link
LDFLAGS      = -g -nostdlib -T ld_ram.lds


OBJS = main.o ctr0.o init.o memfuncs.o led.o
EXE  = main.exe

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

.PHONY: startjlinkgdb debug

startjlinkgdb:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug: $(EXE)
	$(GDB) $<

clean:
	rm -f $(EXE)
	rm -f $(OBJS)
