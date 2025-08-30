#include <mem/gdt.h>

static struct gdt_t gdtr;

void init_gdt() {
  lgdt(&gdtr);
}
