#include "serial.h"

i32 serialInit(void) {
    outb(PORT + 1, 0x00);    // Disable all interrupts
    outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(PORT + 1, 0x00);    //                  (hi byte)
    outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    outb(PORT + 4, 0x1E);    // Set in loopback mode, test the serial chip
    outb(PORT + 0, 0xAE);    // Test serial chip (send byte 0xAE and check if serial returns same byte)

    // Check if serial is faulty (i.e: not same byte as sent)
    if (inb(PORT + 0) != 0xAE) {
        return 0;
    }

    // If serial is not faulty set it in normal operation mode
    // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
    outb(PORT + 4, 0x0F);
    return 1;
}

i32 serialReceived() {
    return inb(PORT + 5) & 1;
}

char serialRead() {
    while (!serialReceived());
    return inb(PORT);
}

i32 serialIsTransmitEmpty() {
    return inb(PORT + 5) & 0x20;
}

void serialPutc(char a) {
    while (!serialIsTransmitEmpty());
    outb(PORT, a);
}

void serialPuts(char *a) {
    while (*a) {
        serialPutc(*a);
        a++;
    }
}

void serialPrintf(char *format, ...) {
    i32 i;
    u32 u;
    char *s;
    char *traverse;

    __builtin_va_list arg;
    __builtin_va_start(arg, format);

    for (traverse = format; *traverse; traverse++) {
        while (*traverse != '%') {
            serialPutc(*traverse);
            traverse++;
            if(!*traverse) return;
        }

        traverse++;

        switch (*traverse) {
            case '%':
                serialPutc('%');
                break;
            case 'c' :
                i = __builtin_va_arg(arg, int);     //Fetch char argument
                serialPutc((char) i);
                break;
            case 'd' :
                i = __builtin_va_arg(arg, int);         //Fetch Decimal/Integer argument
                serialPuts(itoa(i, 10));
                break;
            case 'o':
                u = __builtin_va_arg(arg, u32); //Fetch Octal representation
                serialPuts(uitoa(u, 8));
                break;
            case 's':
                s = __builtin_va_arg(arg, char *);       //Fetch string
                serialPuts(s);
                break;
            case 'x':
                u = __builtin_va_arg(arg, u32); //Fetch Hexadecimal representation
                serialPuts(uitoa(u, 16));
                break;
            case 0:
                return;
        }
    }

    __builtin_va_end(arg);
}