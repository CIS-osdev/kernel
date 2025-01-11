.section .multiboot
.code32

.extern bss_start
.extern end
.extern phys

.set MULTIBOOT2_MAGIC,             0xE85250D6
.set MULTIBOOT2_ARCHITECTURE,      0  # 0 for i386, 4 for MIPS, etc.
.set MULTIBOOT2_HEADER_LENGTH,     (multiboot2_header_end - multiboot2_header)
.set MULTIBOOT2_CHECKSUM,          -(MULTIBOOT2_MAGIC + MULTIBOOT2_ARCHITECTURE + MULTIBOOT2_HEADER_LENGTH)

.align 8
multiboot2_header:
    .long MULTIBOOT2_MAGIC
    .long MULTIBOOT2_ARCHITECTURE
    .long MULTIBOOT2_HEADER_LENGTH
    .long MULTIBOOT2_CHECKSUM

    # Information request tag
    .align 8
    .short 1  # Type: Information request
    .short 0  # Flags: None
    .long 20  # Size: 20 bytes
    .long 4   # Request memory information
    .long 6   # Request boot loader name
    .long 8   # Request BIOS boot device
    .long 9   # Request memory map

    # Address tag
    .align 8
    .short 2  # Type: Address
    .short 0  # Flags: None
    .long 24  # Size: 24 bytes
    .long multiboot2_header  # Header address
    .long phys              # Load address
    .long bss_start         # Load end address
    .long end               # BSS end address

    # Entry address tag
    .align 8
    .short 3  # Type: Entry address
    .short 0  # Flags: None
    .long 12  # Size: 12 bytes
    .long _start  # Entry point address

    # Video mode tag
    .align 8
    .short 5  # Type: Video mode
    .short 0  # Flags: None
    .long 20  # Size: 20 bytes
    .long 1280  # Width
    .long 800   # Height
    .long 32    # Depth

    # End tag
    .align 8
    .short 0  # Type: End
    .short 0  # Flags: None
    .long 8   # Size: 8 bytes

multiboot2_header_end:

.section .stack, "aw", @nobits
stack_bottom:
    .skip 16384
.global stack_top
stack_top:

.section .bootstrap
.code32
.align 4

.extern paging_main
.extern jmp_long
.type jmp_long, @function

.extern kernel_main64
.type kernel_main64, @function

.global _start
.type _start, @function
_start:
    movl %ebx, %ecx
    addl $16, %ecx
    mov %ecx, %esp
    call _forward
_forward:
    popl %ecx
    subl $_forward, %ecx

    mov $stack_top, %esp
    addl %ecx, %esp
    and $-16, %esp

    pushl $0
    pushl %esp
    pushl $0
    pushl %eax
    pushl $0
    pushl %ebx

    jmp jmp_long

.align 4

jmp_long:
    mov $paging_main, %edi
    addl %ecx, %edi
    pushl %ecx

    mov $0x1007, %eax
    add %edi, %eax
    mov %eax, (%edi)

    add $0x1000, %edi
    mov $0x1003, %eax
    add %edi, %eax
    mov %eax, (%edi)

    add $0x1000, %edi

    mov $0x87, %ebx
    mov $32, %ecx

.set_entry:
    mov %ebx, (%edi)
    add $0x200000, %ebx
    add $8, %edi
    loop .set_entry

    mov $paging_main, %edi
    popl %ecx
    addl %ecx, %edi
    pushl %ecx
    mov %edi, %cr3

    mov %cr4, %eax
    or $32, %eax
    mov %eax, %cr4

    mov $0xC0000080, %ecx
    rdmsr
    or $256, %eax
    wrmsr

    mov %cr0, %eax
    or $0x80000000, %eax
    mov %eax, %cr0

    popl %ecx

    lea (_lgdt+3)(%ecx), %eax
    movl (%eax), %ebx
    addl %ecx, %ebx
    movl %ebx, (%eax)

    lea (gdtr+2)(%ecx), %eax
    movl (%eax), %ebx
    addl %ecx, %ebx
    movl %ebx, (%eax)

    lea (_ljmp+1)(%ecx), %eax
    movl (%eax), %ebx
    addl %ecx, %ebx
    movl %ebx, (%eax)

    pushl $0
    pushl %ecx

_lgdt:
    lgdt gdtr

_ljmp:
    ljmp $0x08, $amd64

.align 8
gdtr:
    .word gdt_end - gdt_base
    .quad gdt_base

gdt_base:
    .quad 0
    .word 0
    .word 0
    .byte 0
    .byte 0x9a
    .byte 0x20
    .byte 0
    .word 0xffff
    .word 0
    .byte 0
    .byte 0x92
    .byte 0
    .byte 0
gdt_end:

.code64
.align 8
.section .bootstrap

amd64:
    cli
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    finit

    cli
    pop %rcx
    pop %rdi
    pop %rsi
    pop %rdx
    callq kernel_main64

halt:
    cli
    hlt
    jmp halt
