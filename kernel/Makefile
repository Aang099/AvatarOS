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
CFLAGS+=-nostdinc -ffreestanding -static -nostartfiles -nostdlib -s
CFLAGS+=-fno-pie -fno-stack-protector -fno-builtin-function -fno-builtin -fno-pic
CCFLAGS=-std=c11 -I.
CCFLAGS+=-Wno-pointer-arith -Wno-unused-parameter
CXXFLAGS=-fno-exceptions -fno-rtti -nostdlib++
ASFLAGS=-O2
NASMFLAGS=-felf32
LDFLAGS=-Tlinker.ld -fno-exceptions -fno-rtti

ifeq ($(UNAME),Linux)
CCFLAGS+=-elf_i386
endif

KERNEL_C_kernelS=$(wildcard ./*.c ./**/*.c ./**/**/*.c)
KERNEL_CXX_kernelS=$(wildcard ./*.cpp ./**/*.cpp ./**/**/*.cpp)
KERNEL_S_kernelS=$(wildcard ./*.s ./**/*.s ./**/**/*.s)
KERNEL_NASM_kernelS=$(wildcard ./*.asm ./**/*.asm ./**/**/*.asm)
KERNEL_OBJS=$(KERNEL_C_kernelS:.c=.o) $(KERNEL_CXX_kernelS:.cpp=.o) $(KERNEL_S_kernelS:.s=.o) $(KERNEL_NASM_kernelS:.asm=.o)

KERNEL=../isodir/boot/kernel

clean:
	rm -f ./*.o
	rm -f ./**/*.o
	rm -f ./**/**/*.o

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(CCFLAGS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CFLAGS0) $(CCFLAGS) $(CXXFLAGS)

%.o: %.s
	$(AS) -o $@ -c $< $(ASFLAGS)
%.o: %.asm
	$(NASM) -o $@ $< $(NASMFLAGS)

build: $(KERNEL_OBJS)
	$(CXX) -o $(KERNEL) $^ $(CFLAGS) $(LDFLAGS)