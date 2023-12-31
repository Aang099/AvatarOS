#include "interrupts.h"

void (*handlers[32])(struct registers *regs) = { 0 };

void irqStub(struct registers *regs) {
    if (regs->int_no <= 47 && regs->int_no >= 32) {
        if (handlers[regs->int_no - 32]) {
            handlers[regs->int_no - 32](regs);
        }
    }

    if (regs->int_no >= 0x40) {
        outb(PIC2, PIC_EOI);
    }

    outb(PIC1, PIC_EOI);
}

void remapIrqs(void) {
    u8 mask1 = inb(PIC1_DATA), mask2 = inb(PIC2_DATA);
    outb(PIC1, ICW1_INIT | ICW1_ICW4);
    outb(PIC2, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, PIC1_OFFSET);
    outb(PIC2_DATA, PIC2_OFFSET);
    outb(PIC1_DATA, 0x04); // PIC2 at IRQ2
    outb(PIC2_DATA, 0x02); // Cascade indentity
    outb(PIC1_DATA, PIC_MODE_8086);
    outb(PIC1_DATA, PIC_MODE_8086);
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

void setIrqMask(u8 i) {
    u16 port = i < 8 ? PIC1_DATA : PIC2_DATA;
    u8 value = inb(port) | (1 << i);
    outb(port, value);
}

void clearIrqMask(u8 i) {
    u16 port = i < 8 ? PIC1_DATA : PIC2_DATA;
    u8 value = inb(port) & ~(1 << i);
    outb(port, value);
}

void installIrq(u8 i, void (*handler)(struct registers *)) {
    __asm __volatile("cli");
    handlers[i] = handler;
    clearIrqMask(i);
    __asm __volatile("sti");
}