.section .multiboot
.align 8

.long 0x1BADB002
.long 0x00000003
.long -(0x1BADB002 + 0x00000003)

.section .bss
.align 16
stack_bottom:
    .skip 1024 * 4
stack_top:

.section .text
.code32
.global _start
_start:
    movl $0xFFFFFFFF, %esp

    movl $0x80000000, %eax
    cpuid
    cmpl $0x80000001, %eax
    jb no_long_mode
    movl $0x80000001, %eax
    cpuid
    testl $0x20000000, %edx
    jnz long_mode_supported
no_long_mode:
    hlt
long_mode_supported:
    # PAE
    movl %cr4, %eax
    orl $0x20, %eax
    movl %eax, %cr4

    # GDT
    call gdt64_install

    # IDT
    call idt_install

    # AMD64
    movl $0x101, %eax
    movl %eax, %cr0
    movl %cr0, %eax
    orl $0x80000000, %eax
    movl %eax, %cr0

    ljmp $0x08, $enter_long_mode

.code64
enter_long_mode:
    movw $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss

    movq stack_top, %rsp

    call kernel_main64

    cli
    hlt
