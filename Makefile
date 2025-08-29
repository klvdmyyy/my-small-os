OBJECTS := loader.o kmain.o framebuffer.o io.o

CC := gcc
CFLAGS := -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LD := ld
LDFLAGS := -T link.ld -melf_i386

AS := nasm
ASFLAGS := -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	mkdir -p bin
	$(LD) $(LDFLAGS) $(OBJECTS) -o bin/kernel.elf

run: bin/kernel.elf
	qemu-system-i386 -kernel $^

%.o: %.c
	$(CC) $(CFLAGS)	 $< -o $@

%.o: %.nasm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o bin/kernel.elf
