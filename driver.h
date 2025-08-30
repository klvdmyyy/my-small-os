#pragma once

#include "types.h"

int fb_write(char *buf, uint32_t len);

#ifdef USE_WRITE_DRIVER

typedef int (*writable_t)(char*, uint32_t);
#define DECLARE_WRITABLE(name, fn)              \
  static volatile writable_t name = fn

int write(writable_t w, char *buf);

DECLARE_WRITABLE(framebuffer, fb_write);

#endif /* USE_WRITE_DRIVER */
