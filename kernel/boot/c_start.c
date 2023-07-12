#include "multiboot.h"
#include "../screen/font.h"
#include "../io/serial.h"
#include "../x86/arch.h"

_Noreturn void hang() {
    for(;;) {
        __asm __volatile("cli");
        __asm __volatile("hlt");
    }
}

void c_init(u32 magic) {
    if(magic != 0x2BADB002) hang();
    //multiboot_info_t *mb_info = (multiboot_info_t*) 0xC03FF000;
    serialInit();
    setupGdt();
    setupIdt();
    vbeSetup(1080, 720);
    fontStr(uitoa(magic, 16), 8, 0, 0, 0xffffffff);
    hang();

}

