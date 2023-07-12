
# Declare constants for the multiboot header.
.set FLAGS,    1<<2 | 1<<1 | 1            # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a multiboot header that marks the program as a kernel.
.section .multiboot.data, "aw"
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.skip 20
.long 0
.long 320
.long 200
.long 32

# Allocate the initial stack.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 65536 # 64 KiB
stack_top:

# The kernel entry point.
.section .multiboot.text, "a"
.global _start
.type _start, @function
_start:
    cli
	# Physical address of bootPageTable.
	movl $(bootPageTable - 0xC0000000), %edi
	# First address to map is address 0.
	movl $0, %esi
	# Map 1023 pages. The 1024th page will be mapped to the location of the multiboot structure
	movl $1023, %ecx

1:
	# Only map the kernel.
	cmpl $_kernel_start, %esi
	jl 2f
	cmpl $(_kernel_end - 0xC0000000), %esi
	jge 3f

	# Map physical address as "present, writable". Note that this maps
	# .text and .rodata as writable. Mind security and map them as non-writable.
	movl %esi, %edx
	orl $0x003, %edx
	movl %edx, (%edi)

2:
	# Size of page is 4096 bytes.
	addl $4096, %esi
	# Size of entries in bootPageTable is 4 bytes.
	addl $4, %edi
	# Loop to the next entry if we haven't finished.
	loop 1b

3:
	# Map multiboot structure to 0xC03FF000 as "present, writable".
	andl $0xfffff000, %ebx
	addl $3, %ebx
	movl %ebx, bootPageTable - 0xC0000000 + 4092

	# The page table is used at both page directory entry 0 (virtually from 0x0
	# to 0x3FFFFF) (thus identity mapping the kernel) and page directory entry
	# 768 (virtually from 0xC0000000 to 0xC03FFFFF) (thus mapping it in the
	# higher half). The kernel is identity mapped because enabling paging does
	# not change the next instruction, which continues to be physical. The CPU
	# would instead page fault if there was no identity mapping.

	# Map the page table to both virtual addresses 0x00000000 and 0xC0000000.
	movl $(bootPageTable - 0xC0000000 + 0x003), pageDirectory - 0xC0000000 + 0
	movl $(bootPageTable - 0xC0000000 + 0x003), pageDirectory - 0xC0000000 + 768 * 4

	# Set cr3 to the address of the pageDirectory.
	movl $(pageDirectory - 0xC0000000), %ecx
	movl %ecx, %cr3

	# Enable paging and the write-protect bit.
	movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0

	# Jump to higher half with an absolute jump.
	lea 4f, %ecx
	jmp *%ecx

.section .text

4:
	# At this point, paging is fully set up and enabled.

	# Unmap the identity mapping as it is now unnecessary.
	movl $0, pageDirectory + 0

	# Reload crc3 to force a TLB flush so the changes to take effect.
	movl %cr3, %ecx
	movl %ecx, %cr3

	# Set up the stack.
	mov $stack_top, %esp

	# Enter the high-level kernel.
	push %eax
	call c_init

	# Theoretically, c_init should never return. If it somehow does, loop infinitely.
	cli
1:	hlt
	jmp 1b
