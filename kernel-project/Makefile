
ASM=nasm
CC=gcc
LD=ld

all: kernel.iso

build:
	mkdir -p build

build/header.o: src/boot/header.asm | build
	$(ASM) -f elf64 $< -o $@

build/boot.o: src/boot/boot.asm | build
	$(ASM) -f elf64 $< -o $@

build/long_mode.o: src/boot/long_mode.asm | build
	$(ASM) -f elf64 $< -o $@

build/main.o: src/kernel/main.c | build
	$(CC) -m64 -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone -c $< -o $@

build/print.o: src/kernel/print.c | build
	$(CC) -m64 -ffreestanding -fno-stack-protector -fno-pic -mno-red-zone -c $< -o $@

build/kernel.bin: build/header.o build/boot.o build/long_mode.o build/main.o build/print.o
	$(LD) -n -T targets/x86_64/linker.ld -o $@ $^

kernel.iso: build/kernel.bin
	mkdir -p build/isofiles/boot/grub
	cp build/kernel.bin build/isofiles/boot/kernel.bin
	cp targets/x86_64/grub.cfg build/isofiles/boot/grub/grub.cfg
	grub-mkrescue -o $@ build/isofiles

run: kernel.iso
	qemu-system-x86_64 -cdrom kernel.iso -display curses

clean:
	rm -rf build kernel.iso
