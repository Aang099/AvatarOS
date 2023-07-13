#include "pci.h"

u32 pciRead(u8 bus, u8 device, u8 function, u8 offset) {
    u32 reg = (u32) ((bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC) | ((u32) 0x80000000));
    outl(PCI_CONFIG, reg);

    return inl(PCI_DATA);
}

void pciWrite(u8 bus, u8 device, u8 function, u8 offset, u32 data) {
    u32 reg = 0x80000000;

    reg |= (bus & 0xFF) << 16;
    reg |= (device & 0x1F) << 11;
    reg |= (function & 0x7) << 8;
    reg |= offset & 0xFC;

    outl(PCI_CONFIG, reg);
    outl(PCI_DATA, data);
}

u8 pciFind(u16 vendor, u16 device, u8 *bus, u8 *dev, u8 *function) {
    u32 vend_dev, my_vend_dev;

    my_vend_dev = (vendor & 0xFFFF) | (device << 16);

    for (u16 b = 0; b < 256; b++)
        for (u8 d = 0; d < 32; d++)
            for (u8 f = 0; f < 8; f++) {
                vend_dev = pciRead(b, d, f, PCI_VENDOR_DEVICE);
                if (vend_dev != 0xFFFF && vend_dev == my_vend_dev) {
                    *bus = b;
                    *dev = d;
                    *function = f;
                    return 1;
                }
            }
    return 0;
}