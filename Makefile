SRCS := $(shell find kernel/ -name "*.c" -o -name "*.s")
OBJS := $(patsubst %.c, %.o, $(patsubst %.s, %.o, $(SRCS)))
$(shell mkdir -p $(dir $(OBJS)))

CFLAGS = -m64 -Wall -Werror -std=gnu11 -Ikernel/include -ffreestanding -O0 -fno-stack-protector 
ASFLAGS = -64

.PHONY: all run test clean format

all: cis-os.iso

cis-os.iso: kernel/kernel.elf boot/grub.cfg
	mkdir -p isodir/boot/grub
	cp kernel/kernel.elf isodir/boot/kernel.elf
	cp boot/grub.cfg isodir/boot/grub/grub.cfg
	cd initrd && find . -print | cpio -o -H newc > ../initrd.cpio && cd ..
	cp initrd.cpio isodir/initrd.cpio
	grub-mkrescue -o cis-os.iso isodir

kernel/kernel.elf: $(OBJS)
	ld -nostdlib -o $@ -T scripts/linker.ld $(OBJS)

%.o: %.c
	gcc $(CFLAGS) -c -o $@ $<

%.o: %.s
	as $(ASFLAGS) -o $@ $<

serial.log: cis-os.iso
	timeout 10s qemu-system-x86_64 -display none -m 256 -cdrom $< -d guest_errors -serial file:$@ --no-reboot -no-shutdown || true

test: serial.log
	cat $<
	ls
	grep -q '\[OK\]' $< && echo "Test passed." || (echo "Test failed." && exit 1)

run: cis-os.iso
	qemu-system-x86_64 -m 256 -cdrom $< -d guest_errors -serial file:serial.log --no-reboot -no-shutdown

clean:
	rm -rf isodir
	rm -rf kernel/kernel.elf cis-os.iso
	find kernel/ -name "*.o" -delete
	rm -f serial.log

format:
	find . -type d -name "3rd" -prune -o -type f \( -name "*.c" -o -name "*.h" \) -print0 | xargs -0 clang-format -i -style=file
