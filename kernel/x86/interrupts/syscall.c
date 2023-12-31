#include "syscall.h"
#include "../../screen/font.h"
#include "../../drivers/serial/serial.h"

void handleSyscallC(struct registers *reg) {
    serialPrintf("%x\n", reg->eax);
    serialPrintf("%s\n", (char*)reg->eax);
    fontStr((char*) reg->eax, strlen((char*) reg->eax), 0, 16, 0xffffffff);
}

extern void handleSyscallAsm(void*);

void setupSyscalls() {
    idtSet(0x80, handleSyscallAsm, 0x08, 0x8E); //todo find out the actual flags
}
