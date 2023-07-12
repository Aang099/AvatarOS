#include "bochs.h"

u16 screenWidth, screenHeight;
u32 *screenBuffer;
u32 screenPageTable[1024] __attribute((aligned(4096))) = {0};

void vbeWrite(u16 index, u16 value) {
    outw(VBE_DISPI_IOPORT_INDEX, index);
    outw(VBE_DISPI_IOPORT_DATA, value);
}

u16 vbeRead(u16 index) {
    outw(VBE_DISPI_IOPORT_INDEX, index);
    return inw(VBE_DISPI_IOPORT_DATA);
}

void vbeDisable(void) {
    vbeWrite(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
}

void vbeEnable() {
    vbeWrite(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);
}

void vbeSetup(u16 width, u16 height) {
    u32 bufferPhysicalAddr;
    vbeDisable();
    vbeWrite(VBE_DISPI_INDEX_XRES, width);
    vbeWrite(VBE_DISPI_INDEX_YRES, height);
    vbeWrite(VBE_DISPI_INDEX_BPP, 32);
    vbeWrite(VBE_DISPI_INDEX_VIRT_WIDTH, width);
    vbeWrite(VBE_DISPI_INDEX_Y_OFFSET, 0);
    vbeEnable();
    screenWidth = width;
    screenHeight = height;

    u8 bus = 0, dev = 0, func = 0;
    if (pciFind(BOCHS_VBE_VENDOR, BOCHS_VBE_DEVICE, &bus, &dev, &func)
        || pciFind(0x80EE, 0xBEEF, &bus, &dev, &func)) {
        bufferPhysicalAddr = pciRead(bus, dev, func, PCI_BAR0);
    } else {
        bufferPhysicalAddr = 0xE0000000;
    }
    u16 screenPageCount = (screenWidth * screenHeight * 4 + (bufferPhysicalAddr & 0xfff)) / 4096;
    u32 bufferPageAddr = bufferPhysicalAddr & 0xfffff000;
    if (screenPageCount < 1024) {
        for (int i = 0; i < screenPageCount; i++) {
            screenPageTable[i] = bufferPageAddr + i * 4096 + PAGE_TABLE_FLAG_PRESENT + PAGE_TABLE_FLAG_WRITABLE;
        }
        if(!addPageTable(screenPageTable, 0xD0000000, PAGE_DIRECTORY_FLAG_WRITABLE)) {
            //todo implement panic
        }
        screenBuffer = (u32 *) 0xD0000000;
    } else return; //todo account for screen sizes larger than 4mb / one page table
}

