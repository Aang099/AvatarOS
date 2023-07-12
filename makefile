UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
	CC=gcc
	CXX=g++
	AS=as --32
	# LD = ld -m i386_elf
	LD=g++
else
	CC=i386-elf-gcc
	CXX=i386-elf-g++
	AS=i386-elf-as
	# LD = i386-elf-ld
	LD=i386-elf-g++
endif
NASM=nasm

CFLAGS=-m32 -O2 -g
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-nostdinc -ffreestanding -static -nostartfiles -nolibc -s
CFLAGS+=-fno-pie -fno-stack-protector -fno-builtin-function -fno-builtin -fno-pic
CCFLAGS=-std=c11
CCFLAGS+=-Wno-pointer-arith -Wno-unused-parameter
CXXFLAGS=-fno-exceptions -fno-rtti -nostdlib++
ASFLAGS=-O2
NASMFLAGS=-felf32
LDFLAGS=-Tlinker.ld -static-libgcc -fno-exceptions -fno-rtti

ifeq ($(UNAME),Linux)
CCFLAGS+=-elf_i386
endif

KERNEL_C_kernelS=$(wildcard kernel/**/*.c)
KERNEL_CXX_kernelS=$(wildcard kernel/**/*.cpp)
KERNEL_S_kernelS=$(wildcard kernel/**/*.s)
KERNEL_NASM_kernelS=$(wildcard kernel/**/*.asm)
KERNEL_OBJS=$(KERNEL_C_kernelS:.c=.o) $(KERNEL_CXX_kernelS:.cpp=.o) $(KERNEL_S_kernelS:.s=.o) $(KERNEL_NASM_kernelS:.asm=.o)

KERNEL=isodir/boot/kernel

all: clean iso

clean:
	rm -f ./**/*.o
	rm -f ./**/**/*.o
	rm -f ./*.img
	rm -f ./**/*.elf
	rm -f ./**/*.bin

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CCFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CFLAGS0) $(CCFLAGS) $(CXXFLAGS)

%.o: %.s
	$(AS) -o $@ -c $< $(ASFLAGS)
%.o: %.asm
	$(NASM) -o $@ $< $(NASMFLAGS)

kernel: $(KERNEL_OBJS)
	$(CXX) -o $(KERNEL) $^ $(CFLAGS) $(LDFLAGS)

iso: kernel
	grub-mkrescue isodir -o mykernel.iso

run: all
	bochs -q