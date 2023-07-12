#include "kstd.h"

void outb(u32 port, u8 value) {
    __asm __volatile("outb %%al,%%dx"::"d" (port), "a" (value));
}

void outw(u32 port, u16 value) {
    __asm __volatile("outw %%ax,%%dx"::"d" (port), "a" (value));
}


void outl(u32 port, u32 value) {
    __asm __volatile("outl %%eax,%%dx"::"d" (port), "a" (value));
}

u8 inb(u32 port) {
    u8 ret;
    __asm __volatile("inb %%dx,%%al":"=a" (ret):"d"(port));
    return ret;
}

u16 inw(u32 port) {
    u16 ret;
    __asm __volatile("inw %%dx,%%ax":"=a" (ret):"d"(port));
    return ret;
}

u32 inl(u32 port) {
    u32 ret;
    __asm __volatile("inl %%dx,%%eax":"=a" (ret):"d"(port));
    return ret;
}