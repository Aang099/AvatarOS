#include "kstd.h"

static const char *chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char charBuffer[32] = {0};

void *memset(void *s, int c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char *) s)[i] = (char) c;
    }
    return s;
}

void *memcpy(void *restrict dest, const void *restrict src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char *) dest)[i] = ((char *) src)[i];
    }
    return dest;
}

size_t strlen(const char *s) {
    size_t i = 0;
    while (*s++) i++;
    return i;
}

char *itoa(i32 x, u8 base) {
    i32 i = 0, j;
    u8 tmp;

    u32 y = abs(x);
    do {
        tmp = y % base;
        charBuffer[i++] = chars[tmp];
    } while (y /= base);
    if(x < 0)
        charBuffer[i++] = '-';

    charBuffer[i--] = 0;
    for (j = 0; j < i; j++, i--) {
        tmp = charBuffer[j];
        charBuffer[j] = charBuffer[i];
        charBuffer[i] = (char) tmp;
    }
    return charBuffer;
}

char *uitoa(u32 x, u8 base) {
    i32 i = 0, j;
    u8 tmp;

    do {
        tmp = x % base;
        charBuffer[i++] = chars[tmp];
    } while (x /= base);

    charBuffer[i--] = 0;
    for (j = 0; j < i; j++, i--) {
        tmp = charBuffer[j];
        charBuffer[j] = charBuffer[i];
        charBuffer[i] = (char) tmp;
    }
    return charBuffer;
}

