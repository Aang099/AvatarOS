#include "interrupts.h"
static struct {
    struct idt_entry entries[256];
    struct idt_ptr pointer;
} __attribute((packed)) idt;

extern void loadIdt(void* ptr);

void idtSet(u8 index, void (*base)(struct registers*), u16 selector, u8 flags) {
    idt.entries[index] = (struct idt_entry) {
            .offset_low = ((u32) base) & 0xFFFF,
            .offset_high = (((u32) base) >> 16) & 0xFFFF,
            .selector = selector,
            .type = flags | 0x60,
    };
}

void setupInterrupts(void) {
    idt.pointer.limit = sizeof(idt.entries) - 1;
    idt.pointer.base = (u32*) &idt.entries[0];
    memset(&idt.entries[0], 0, sizeof(idt.entries));
    loadIdt((u32*) &idt.pointer);
    //setupIsrs();
    //remapIrqs();
}