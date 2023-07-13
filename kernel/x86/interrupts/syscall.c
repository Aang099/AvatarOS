#include "syscall.h"
#include "../../screen/font.h"
#include "../../io/serial.h"

void handleSyscallC(struct registers *reg) {
    serialPuts("Syscall!\n");
    fontStr("Syscall!", 4, 0, 16, 0xffffffff);
}

extern void handleSyscallAsm(void*);

void setupSyscalls() {
    idtSet(0x80, handleSyscallAsm, 0x08, 0x8E); //todo find out the actual flags
}
