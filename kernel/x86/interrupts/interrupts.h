#pragma once
#include "../arch.h"

#define PIC1 0x20
#define PIC1_OFFSET 0x20
#define PIC1_DATA (PIC1 + 1)

#define PIC2 0xA0
#define PIC2_OFFSET 0x28
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI 0x20
#define PIC_MODE_8086 0x01
#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10

#define NUM_ISRS 48

#define PIC_WAIT() do {         \
        asm ("jmp 1f\n\t"       \
                "1:\n\t"        \
                "    jmp 2f\n\t"\
                "2:");          \
    } while (0)

struct idt_entry {
    u16 offset_low;
    u16 selector;
    u8 ignored __attribute((unused));
    u8 type;
    u16 offset_high;
} __attribute((packed));

struct idt_ptr {
    u16 limit;
    u32* base;
} __attribute((packed));

struct registers {
    u32 gs, fs, es, ds;
    u32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    u32 int_no, err_no;
    u32 eip, cs, efl, useresp, ss;
} __attribute((packed));

void setupInterrupts(void);
void setupIsrs(void);
void remapIrqs(void);
void idtSet(u8 index, void (*base)(), u16 selector, u8 flags);
void installIrq(u8 i, void (*handler)(struct registers *));
void irqStub(struct registers *regs);

extern void (*isrHandlers[])(struct registers*);
