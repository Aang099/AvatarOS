all: clean build

clean:
	rm -f isodir/boot/kernel
	make -C kernel clean


build:
	make -C kernel build
	grub-mkrescue isodir -o mykernel.iso

run: all
	bochs -q