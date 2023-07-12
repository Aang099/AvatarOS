#pragma once

#include "bochs.h"

void fontChar(char c, u16 x, u16 y, u32 color);
void fontStr(const char *s, size_t len, u16 x, u16 y, u32 color);

