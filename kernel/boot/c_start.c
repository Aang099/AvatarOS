#include "multiboot.h"
#include "../screen/font.h"
#include "../io/serial.h"
#include "../x86/x86.h"

_Noreturn void hang() {
    for(;;) {
        __asm __volatile("cli");
        __asm __volatile("hlt");
    }
}

void c_init(u32 magic) {
    if(magic != 0x2BADB002) hang();
    multiboot_info_t *mb_info = (multiboot_info_t*) 0xC03FF000;

    serialInit();
    vbeSetup(1080, 720);
    fontStr(itoa(magic, 16), 8, 0, 0, 0xffffffff);
    char* name = (char*)mb_info->boot_loader_name;
    //fontStr(name, strlen(name), 0, 16, 0xffffffff);
    //screenBuffer[0] = 255;

    hang();

}

