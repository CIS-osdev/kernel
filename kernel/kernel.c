#include <khal.h>
#include <kstdint.h>
#include <kstring.h>

int multiboot2_init(uint64_t *addr, uint32_t magic);

void kernel_main64(uint64_t *multiboot2, uint32_t magic, void *esp, uint64_t base) {
	serial_init( );
	serial_printf(":D\n");
	
	int status = multiboot2_init(multiboot2, magic);

	if (status) {
		serial_printf("[OK]\n");
	} else {
		serial_printf("[ERR]\n");
	}
	char *str1 = "ABCF";
	char *str2 = "ABCD";
	char buf[7] = "";
	auto cmp_value = strcmp(str1, str2);
	
	serial_printf("[LOG] STR1 AND STR2 CMP %d\n", cmp_value);
	serial_printf("[LOG] STR1 LEN %d\n", strlen(str1));
	strcpy((char*)&buf, str1); 
	serial_printf("[LOG] STRCPY RESULT: %s\n", buf);
	serial_printf("[LOG] STRCPY RESULT LEN %d\n", strlen(buf));
	strcat((char*)&buf, "CAT");
	serial_printf("[LOG] STRCAT RESULT: %s\n", buf);
	serial_printf("[LOG] STRCAT RESULT LEN %d\n", strlen(buf));
	for (;;) {}
}
