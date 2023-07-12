#pragma once
#include "../klib/kstd.h"
#define PORT 0x3f8          // COM1

int serialInit();
char serialRead();
void serialPutc(char a);
void serialPuts(char *a);
void serialPrintf(char* format,...);

