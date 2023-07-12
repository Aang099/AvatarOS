.section .text
.global flushPage
.type flushPage, @function
flushPage:
	#movl	4(%esp),%eax
	#invlpg	(%eax)
	movl	%cr3,%eax
	movl	%eax,%cr3
	ret

.global loadGdt
.type loadGdt, @function
loadGdt:
    mov   4(%esp), %eax
    lgdt  (%eax)

    ljmp $8, $reloadSegment

 reloadSegment:               # far jump make CS = 0x08
    mov  $0x10, %ax              # 0x10 = kernel data segment
    mov  %ax, %ds
    mov  %ax, %es
    mov  %ax, %fs
    mov  %ax, %gs
    mov  %ax, %ss
    ret

.global loadTss
.type loadTss, @function
loadTss:
    mov   $0x2B, %ax
    ltr   %ax
    ret

.global loadIdt
.type loadIdt, @function
loadIdt:
    mov 4(%esp), %eax
    lidt (%eax)
    ret

