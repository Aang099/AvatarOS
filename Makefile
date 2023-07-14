all: clean build

ISO=avataros.iso

clean:
	rm -f isodir/boot/kernel
	make -C kernel clean


build:
	make -C kernel build
	grub-mkrescue isodir -o avataros.iso

qemu: all
	qemu-system-i386 avataros.iso

bochs: all
	bochs -q

