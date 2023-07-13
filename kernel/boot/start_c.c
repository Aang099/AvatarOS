#include "multiboot.h"
#include "../screen/font.h"
#include "../x86/interrupts/syscall.h"

//multiboot_info_t *mb_info = (multiboot_info_t*) 0xC03FF000;

__attribute((noreturn)) void hang(void) {
    for(;;) {
        __asm __volatile("cli");
        __asm __volatile("hlt");
    }
}

void mapMultibootMmap() {

}

extern void syscallTest(char* addr);

void main(void *mb_info, u32 magic) {
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC) hang();
    serialInit();
    setupGdt();
    setupInterrupts();
    vbeSetup(1080, 720);
    fontStr(uitoa(magic, 16), 8, 0, 0, 0xffffffff);
    setupSyscalls();
    fontStr("hi", 2, 0, 8, 0xffffffff);
    __asm __volatile("int $0x80");
    hang();
}

