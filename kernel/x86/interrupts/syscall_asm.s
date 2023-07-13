.global handleSyscallAsm
.type handleSyscallAsm, @function
# already on stack: ss, sp, flags, cs, ip.
# need to push ax, gs, fs, es, ds, -ENOSYS, bp, di, si, dx, cx, and bx
handleSyscallAsm:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    cld

    push %esp
    call handleSyscallC
    add $4, %esp

    pop %gs
    pop %fs
    pop %es
    pop %ds

    popa

    iret
