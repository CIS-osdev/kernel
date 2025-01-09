#include <kstdint.h>

// We need memory manager and kernel lib first
#if 0
typedef struct {
    char c_magic[6];    // "070701"
    char c_ino[8];
    char c_mode[8];
    char c_uid[8];
    char c_gid[8];
    char c_nlink[8];
    char c_mtime[8];
    char c_filesize[8];
    char c_devmajor[8];
    char c_devminor[8];
    char c_rdevmajor[8];
    char c_rdevminor[8];
    char c_namesize[8];
    char c_check[8];
} cpio_header_t;

void cpio_from_memory(const char *cpio, uint64_t len) {
    const char *ptr = cpio;
    const char *end = cpio + len;

    while (ptr + sizeof(cpio_header_t) <= end) {
        const cpio_header_t *hdr = (const cpio_header_t *)ptr;

        if (memcmp(hdr->c_magic, "070701", 6) != 0) {
            if (memcmp(hdr->c_magic, "000000", 6) == 0) {
                printf("End of archive reached.\n");
                break;
            } else {
                printf("Invalid cpio magic number.\n");
                return;
            }
        }

        uint64_t namesize = strtoul(hdr->c_namesize, NULL, 16);
        uint64_t filesize = strtoul(hdr->c_filesize, NULL, 16);

        uint64_t name_padding = (namesize + 3) & ~3;
        ptr += sizeof(cpio_header_t);

        if (ptr + namesize > end) {
            printf("Error: Not enough data for file name.\n");
            return;
        }
        char *name = malloc(namesize + 1);
        if (!name) {
            printf("Memory allocation failed.\n");
            return;
        }
        memcpy(name, ptr, namesize);
        name[namesize] = '\0';
        printf("File name: %s\n", name);
        free(name);

        ptr += name_padding;

        if (ptr + filesize > end) {
            printf("Error: Not enough data for file content.\n");
            return;
        }
        printf("File size: %llu bytes\n", filesize);

        ptr += (filesize + 3) & ~3;

        if (ptr > end) {
            printf("Error: Overran buffer.\n");
            return;
        }
    }
}
#endif