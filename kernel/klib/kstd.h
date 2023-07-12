#pragma once
#include "ktype.h"

//string
void *memset(void *s, int c, size_t n);
void *memcpy(void *restrict dest, const void *restrict src, size_t n);
size_t strlen(const char* s);
char *itoa(i32 x, u8 base);
char *uitoa(u32 x, u8 base);

//port out
void outb(u32 port, u8 value);
void outw(u32 port, u16 value);
void outl(u32 port, u32 value);

//port in
u8 inb(u32 port);
u16 inw(u32 port);
u32 inl(u32 port);

//math;
u32 abs(i32 value);