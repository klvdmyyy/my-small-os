#################### Building ####################

CC := gcc
CFLAGS := -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		  -ffreestanding -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c \
		  -fno-pic -I./source

LD := ld
LDFLAGS := -n -T source/link.ld -melf_i386

AS := nasm
ASFLAGS := -f elf

#################### Sources ####################

SOURCES := $(shell find ./source | grep -E \\.\(c\$\|nasm\$\))

# $(info Source files:)
# $(foreach file,$(SOURCES),$(info $(file)))
# $(info )

OBJECTS := $(foreach src,$(SOURCES),$(addsuffix .o,$(basename $(src))))

# $(info Object files:)
# $(foreach file,$(OBJECTS),$(info $(file)))
# $(info )

#################### Features ####################

# Enable first write driver.
CFLAGS += -DUSE_WRITE_DRIVER

#################### Targets ####################

all: kernel.elf

kernel.elf: $(OBJECTS)
	@mkdir -p bin
	@echo "	 [LD]	$@"
	@$(LD) $(LDFLAGS) $(OBJECTS) -o bin/kernel.elf

run: bin/kernel.elf
	@qemu-system-i386 -kernel $^ # -serial stdio

%.o: %.c
	@echo "	 [CC]	$@"
	@$(CC) $(CFLAGS)	 $^ -o $@

%.o: %.nasm
	@echo "	 [NASM] $@"
	@$(AS) $(ASFLAGS) $^ -o $@

clean:
	@rm -rf bin/kernel.elf
	@rm -rf *.o
	@rm -rf source/*.o
	@rm -rf sourec/io/*.o
