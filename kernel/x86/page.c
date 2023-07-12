#include "page.h"

u32 pageDirectory[1024] __attribute((aligned(4096))) = {0};

u32 bootPageTable[1024] __attribute((aligned(4096))) = {0};

/*void pageFlush() {
    __asm __volatile("movl %cr3,%eax");
    __asm __volatile("movl %eax,%cr3");
}*/
extern void flushPage();
void addPageTable(const u32 *table, u32 addr, u16 flags) {
    table -= 0x30000000;
    u32 index = addr >> 22;
    if((pageDirectory[index] & PAGE_DIRECTORY_FLAG_PRESENT)) {
        return;
    } // todo error handling
    pageDirectory[index] = ((u32) table & 0xfffff000) + (flags | PAGE_DIRECTORY_FLAG_PRESENT);
    flushPage();
}

