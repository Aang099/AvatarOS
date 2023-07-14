#pragma once

#include "../../util/kstd.h"

#define PCI_CONFIG  0xCF8
#define PCI_DATA    0xCFC

#define PCI_VENDOR_DEVICE   0x00
#define PCI_CLASS_SUBCLASS  0x08

#define PCI_BAR0    0x10
#define PCI_BAR1    PCI_BAR0 + 4
#define PCI_BAR2    PCI_BAR1 + 4
#define PCI_BAR3    PCI_BAR2 + 4
#define PCI_BAR4    PCI_BAR3 + 4
#define PCI_BAR5    PCI_BAR4 + 4

u32 pciRead(u8 bus, u8 device, u8 function, u8 offset);
void pciWrite(u8 bus, u8 device, u8 function, u8 offset, u32 data);
u8 pciFind(u16 vendor, u16 device, u8 *bus, u8 *dev, u8 *function);

