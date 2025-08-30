#include <io/driver.h>
#include <io/framebuffer.h>
#include <util/types.h>

[[maybe_unused]]
static char *my_small_os_header =
  "My Small OS (Microkernel)\n"
  "\n"
  "Copyright (c) 2025 Klementiev Dmitry <klementievd08@yandex.ru>\n"
  "\n"
  "Author:  Klementiev Dmitry <klementievd08@yandex.ru>\n"
  "License: MIT\n"
  "Github:  github.com/klvdmyyy/my-small-os\n"
  "\n"
  "Educational purposes only!!!\n";

struct gdt_t {
  uint32_t address;
  uint16_t size;
} __attribute__((packed));

static uint32_t segments[5];
static struct gdt_t gdtr;

void _lgdt(struct gdt_t *gdt);

void kernel_main() {
  // Framebuffer initializing.
  fb_clear();
  fb_move_cursor(0, 0);

  write(framebuffer, "Initializing GDT...\n");
  gdtr.address = (uint32_t)segments;
  gdtr.size = 5 * sizeof(uint32_t);
  _lgdt(&gdtr);
  write(framebuffer, "GDT is successfully initialized.\n");

  while (1)
    ;
}
