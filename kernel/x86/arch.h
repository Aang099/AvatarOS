#pragma once
#include "../memory/page.h"

struct gdt_entry {
    u32 low;
    u32 high;
} __attribute((packed, aligned(8)));

struct gdt_ptr {
    u16 size;
    u32 offset;
} __attribute((packed));

struct tss_entry
{
    u32 prev_tss;
    u32 esp0;
    u32 ss0;
    u32 esp1;
    u32 ss1;
    u32 esp2;
    u32 ss2;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u32 es;
    u32 cs;
    u32 ss;
    u32 ds;
    u32 fs;
    u32 gs;
    u32 ldt;
    u16 trap;
    u16 iomap_base;
} __attribute((packed));

void setupGdt(void);
void setupTss(void);
