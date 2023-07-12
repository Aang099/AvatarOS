#include "arch.h"

static struct gdt_entry gdtEntries[6] = {{0x00000000, 0x00000000},
                                         {0x0000FFFF, 0x00CF9A00},
                                         {0x0000FFFF, 0x00CF9200},
                                         {0x0000FFFF, 0x00CFFA00},
                                         {0x0000FFFF, 0x00CFF200},
                                         {0x0000FFFF, 0x00000000}}; // this is hideous but the other solution kept crashing
static struct gdt_ptr gdtPtr = {0};

void gdtSet(struct gdt_entry *entry, u32 base, u32 limit, u32 access, u32 flags) {
    entry->low = ((base & 0xFFFF) << 16) | (limit & 0xFFFF);
    entry->high =
            ((base >> 16) & 0xFF) | ((access & 0xFF) << 8) | (((limit >> 16) & 0xF) << 16) | ((flags & 0xF) << 20) |
            (((base >> 24) & 0xFF) << 24);
}

extern void loadGdt(void *ptr);

extern void loadTss();

extern struct tss_entry kernelTss;

void setupGdt() {
    setupTss();
    gdtSet(&gdtEntries[5], (u32) ((&kernelTss) - (0xc0000000 / sizeof(struct tss_entry *))), sizeof(struct tss_entry),
           0x89, 0xC);
    gdtPtr.size = sizeof(struct gdt_entry) * 6;
    gdtPtr.offset = (u32) &gdtEntries[0];
    loadGdt(&gdtPtr);
    loadTss();
}

