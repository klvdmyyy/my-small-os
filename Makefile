OBJECTS := loader.o kmain.o framebuffer.o io.o driver.o

CC := gcc
CFLAGS := -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -ffreestanding -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c \
		  -fno-pic

LD := ld
LDFLAGS := -n -T link.ld -melf_i386

AS := nasm
ASFLAGS := -f elf

# Enable first write driver.
CFLAGS += -DUSE_WRITE_DRIVER

all: kernel.elf

kernel.elf: $(OBJECTS)
	mkdir -p bin
	$(LD) $(LDFLAGS) $(OBJECTS) -o bin/kernel.elf

run: bin/kernel.elf
	qemu-system-i386 -kernel $^ # -serial stdio

%.o: %.c
	$(CC) $(CFLAGS)	 $< -o $@

%.o: %.nasm
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o bin/kernel.elf
