OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

SECTIONS{
	. = 1M;
	phys = .;

	.text BLOCK(4K) : ALIGN(4K) {
		PROVIDE(kernel_section_text_start = .);
		*(.multiboot)
		*(.bootstrap)
		code = .;
		*(.text)
		PROVIDE(kernel_section_text_end = .);
	}

	.rodata BLOCK(4K) : ALIGN(4K) {
		PROVIDE(kernel_section_rodata_start = .);
		*(.rodata)
		PROVIDE(kernel_section_rodata_end = .);
	}

	.data BLOCK(4K) : ALIGN(4K) {
		PROVIDE(kernel_section_data_start = .);
		data = .;
		*(.data)
		*(.symbols)
		PROVIDE(kernel_symbols_start = .);
		PROVIDE(kernel_symbols_end = .);
		PROVIDE(kernel_section_data_end = .);
	}

	.bss BLOCK(4K) : ALIGN(4K) {
		PROVIDE(kernel_section_bss_start = .);
		PROVIDE(bss_start = .);
		bss = .;
		*(COMMON)
		*(.bss)
		*(.stack)
		PROVIDE(kernel_section_bss_end = .);
	}

	end = .;

	/DISCARD/ : {
		*(.comment)
		*(.eh_frame)
		*(.note.gnu.build-id)
	}
}