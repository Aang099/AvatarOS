#pragma once
#include "../util/kstd.h"
#define PORT 0x3f8          // COM1

int serialInit(void);
char serialRead(void);
void serialPutc(char a);
void serialPuts(char *a);
void serialPrintf(char* format,...);

