#pragma once

#include "../klib/ktype.h"
#include "../io/serial.h"

#define PAGE_DIRECTORY_FLAG_PRESENT  (1 << 0)
#define PAGE_DIRECTORY_FLAG_WRITABLE (1 << 1)
#define PAGE_DIRECTORY_FLAG_USER     (1 << 2)
#define PAGE_DIRECTORY_FLAG_WRCACHE  (1 << 3)
#define PAGE_DIRECTORY_FLAG_NOCACHE  (1 << 4)
#define PAGE_DIRECTORY_FLAG_ACCESSED (1 << 5)
#define PAGE_DIRECTORY_FLAG_4MBPAGE  (1 << 7)

#define PAGE_TABLE_FLAG_PRESENT  (1 << 0)
#define PAGE_TABLE_FLAG_WRITABLE (1 << 1)
#define PAGE_TABLE_FLAG_USER     (1 << 2)
#define PAGE_TABLE_FLAG_WRCACHE  (1 << 3)
#define PAGE_TABLE_FLAG_NOCACHE  (1 << 4)
#define PAGE_TABLE_FLAG_ACCESSED (1 << 5)
#define PAGE_TABLE_FLAG_DIRTY    (1 << 6)
#define PAGE_TABLE_FLAG_GLOBAL   (1 << 8)

void addPageTable(const u32 *table, u32 addr, u16 flags);