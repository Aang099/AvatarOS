#include "page.h"

u32 pageDirectory[1024] __attribute((aligned(4096))) = {0};

u32 bootPageTable[1024] __attribute((aligned(4096))) = {0};

u32 **otherPageTables;

void setupPages() {

}

extern void flushPage();
u16 tablesFilled = 0;

char addPageTable(const u32 *table, u32 addr, u16 flags) {
    u32 tableAddr = ((u32) table) - 0xC0000000;
    u32 index = addr >> 22;
    if ((pageDirectory[index] & PAGE_DIRECTORY_FLAG_PRESENT)) {
        return 0;
    } // todo error handling
    pageDirectory[index] = (tableAddr & 0xFFFFF000) + (flags | PAGE_DIRECTORY_FLAG_PRESENT);
    tablesFilled++;
    flushPage();
    return 1;
}

