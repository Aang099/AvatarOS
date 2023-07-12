#pragma once
#include "page.h"

struct gdt {
    u16 size;
    u32 offset;
} __attribute__ ((__packed__));

struct gdt_entry {
    u32 low;
    u32 high;
} __attribute__ ((aligned (8)));