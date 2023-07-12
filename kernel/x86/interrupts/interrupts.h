#pragma once
#include "../../util/kstd.h"
#include "../arch.h"

struct IDTEntry {
    u16 offset_low;
    u16 selector;
    u8 ignored __attribute((unused));
    u8 type;
    u16 offset_high;
} __attribute((packed));

struct IDTPointer {
    u16 limit;
    u32* base;
} __attribute((packed));

void setupIdt();
void idtSet(u8 index, void (*base)(struct registers *), u16 selector, u8 flags) ;