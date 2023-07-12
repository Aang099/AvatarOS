
#include "x86.h"
struct gdt_entry gdtEntries[6];
struct gdt gdt;

void setupGdtEntry(struct gdt_entry* entry, u32 base, u32 limit,
                   u32 access, u32 flags) {

    entry->low = base & 0xFFFF;
    entry->low <<= 16;
    entry->low |= limit & 0xFFFF;

    entry->high = ((base >> 16) & 0xFF) | ((access & 0xFF) << 8) |
                  (((limit >> 16) & 0xF) << 16) | ((flags & 0xF) << 20) |
                  (((base >> 24) & 0xFF) << 24);
}

extern void loadGdt(void* ptr);

void setupGdt() {
    //tss();

    setupGdtEntry(&(gdtEntries[0]), 0x00000000, 0x00000000, 0x00, 0x0);  // null descriptor
    setupGdtEntry(&(gdtEntries[1]), 0x00000000, 0xFFFFFFFF, 0x9A, 0xC);  // kernel code
    setupGdtEntry(&(gdtEntries[2]), 0x00000000, 0xFFFFFFFF, 0x92, 0xC);  // kernel data
    setupGdtEntry(&(gdtEntries[3]), 0x00000000, 0xFFFFFFFF, 0xFA, 0xC);  // user code
    setupGdtEntry(&(gdtEntries[4]), 0x00000000, 0xFFFFFFFF, 0xF2, 0xC);  // user data
    //setupGdtEntry(&(gdtEntries[5]), VIRTUAL_TO_PHYSICAL(&tss), sizeof(tss_entry_t), 0x89, 0xC);

    gdt.size = 8 * 6;
    gdt.offset = (u32)&gdtEntries[0];

    loadGdt(&gdt);
    //load_tss();
}

