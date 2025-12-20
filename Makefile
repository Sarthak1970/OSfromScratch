TARGET   = i686-elf
CC       = $(TARGET)-gcc
AS       = $(TARGET)-as
LD       = $(TARGET)-gcc

CFLAGS   = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS  = -T linker.ld -ffreestanding -O2 -nostdlib

BOOT_SRC    = src/bootloader/boot.s
KERNEL_SRC  = src/kernel/kernel.c

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

$(KERNEL_ELF): $(BOOT_OBJ) $(KERNEL_OBJ)
	$(LD) $(LDFLAGS) -o $@ $^ -lgcc

$(ISO_NAME): $(KERNEL_ELF)
	mkdir -p iso/boot/grub
	cp $(KERNEL_ELF) iso/boot/kernel.elf
	grub-mkrescue -o $(ISO_NAME) iso


run: $(ISO_NAME)
	qemu-system-i386 -cdrom $(ISO_NAME)

clean:
	rm -rf build iso *.iso