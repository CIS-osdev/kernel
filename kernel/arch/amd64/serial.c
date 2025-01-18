#include "kasm.h"
#include <stdint.h>

void serial_write_byte(uint8_t byte) {
	// Wait until the transmit holding register is empty
	while ((inb(0x3f8 + 5) & 0x20) == 0)
		;
	outb(0x3f8, byte);
}

int serial_init() {
	// Disable all interrupts
	outb(0x3f8 + 1, 0x00);

	// Set divisor latch access bit (DLAB) to set baud rate
	outb(0x3f8 + 3, 0x80);

	// Set divisor to 12 for 9600 baud (115200 / 9600 = 12)
	outb(0x3f8, 0x0C);     // Low byte of divisor
	outb(0x3f8 + 1, 0x00); // High byte of divisor (0 for divisor < 256)

	// Disable DLAB and set communication parameters: 8n1 (8 bits, no parity, 1
	// stop bit)
	outb(0x3f8 + 3, 0x03);

	// Enable FIFOs
	outb(0x3f8 + 2, 0xC7); // Enable FIFO, clear Rx and Tx FIFOs

	// Set default line control
	outb(0x3f8 + 4, 0x0B); // Enable FIFO, RTS, DTR

	// Read Line Status Register to clear any pending errors
	inb(0x3f8 + 5);

	return 0;
}