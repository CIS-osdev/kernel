SRCS := $(shell find kernel/ -name "*.c" -o -name "*.s")
OBJS := $(patsubst %.c, %.o, $(patsubst %.s, %.o, $(SRCS)))
$(shell mkdir -p $(dir $(OBJS)))

CFLAGS = -m64 -Wall -Werror -std=gnu11 -Ikernel/include -ffreestanding -O0 
ASFLAGS = -64

all: cis-os.iso

cis-os.iso: kernel/kernel.elf boot/grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel/kernel.elf isodir/boot/kernel.elf
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o cis-os.iso isodir

kernel/kernel.elf: $(OBJS)
	ld -nostdlib -o $@ -T scripts/linker.ld $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

%.o: %.s
	as $(ASFLAGS) -o $@ $<

clean:
	rm -rf isodir
	rm -rf kernel/kernel.elf cis-os.iso
	find kernel/ -name "*.o" -delete

run:
	qemu-system-x86_64 -m 256 -cdrom cis-os.iso