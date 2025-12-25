TARGET   = i686-elf
CC       = $(TARGET)-gcc
AS       = $(TARGET)-as
LD       = $(TARGET)-gcc

CFLAGS   = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I src
LDFLAGS  = -T linker.ld -ffreestanding -O2 -nostdlib

BOOT_SRC    = src/bootloader/boot.s
KERNEL_SRC  = src/kernel/kernel.c

GDT_SRC=src/cpu/gdt/gdt.c
GDT_FLUSH_SRC=src/cpu/gdt/gdt_flush.s
IDT_SRC=src/cpu/interputs/idt.c
ISR_SRC=src/cpu/interputs/isr.s

ISR_OBJ=build/isr.o
IDT_OBJ=build/ist.o

GDT_FLUSH_OBJ=build/gdt_flush.o
GDT_OBJ = build/gdt.o
BOOT_OBJ    = build/boot.o
KERNEL_OBJ  = build/kernel.o
KERNEL_ELF  = build/kernel.elf

ISO_NAME    = s_os.iso

all: $(ISO_NAME)

build:
	mkdir -p build

$(BOOT_OBJ): $(BOOT_SRC) | build
	$(AS) $< -o $@

$(KERNEL_OBJ): $(KERNEL_SRC) | build
	$(CC) $(CFLAGS) -c $< -o $@

$(GDT_OBJ):$(GDT_SRC) | build
	$(CC) $(CFLAGS) -c $< -o $@

$(IDT_OBJ):$(IDT_SRC) | build
	$(CC) $(CFLAGS) -c $< -o $@

$(ISR_OBJ):$(ISR_SRC) | build
	$(AS) $< -o $@

$(GDT_FLUSH_OBJ):$(GDT_FLUSH_SRC) | build
	$(AS) $< -o $@


$(KERNEL_ELF): $(BOOT_OBJ) $(KERNEL_OBJ) $(GDT_OBJ) $(GDT_FLUSH_OBJ) $(IDT_OBJ) $(ISR_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ -lgcc
	
$(ISO_NAME): $(KERNEL_ELF)
	mkdir -p iso/boot/grub
	cp $(KERNEL_ELF) iso/boot/kernel.elf
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(ISO_NAME) iso


run: $(ISO_NAME)
	qemu-system-i386 -cdrom $(ISO_NAME)

clean:
	rm -rf build iso *.iso