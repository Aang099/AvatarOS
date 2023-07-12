#include "arch.h"

struct tss_entry kernelTss = {.ss0 = 0x10, .cs = 0x08, .ss = 0x10, .ds = 0x10, .es = 0x10, .fs = 0x10, .gs = 0x10, .iomap_base = 104}; // 0x08 = kernel code offset, 0x10 = kernel data offset

void setupTss() {
    __asm __volatile("movl %%esp, %0;":"=m"(kernelTss.esp0)::"%eax");
    __asm __volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(kernelTss.cr3)::"%eax");
}