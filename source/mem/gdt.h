#pragma once

#include <util/types.h>

struct gdt_t {
  uint32_t address;
  uint16_t size;
} __attribute__((packed));

void lgdt(struct gdt_t*);
void init_gdt();
