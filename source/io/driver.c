#include "driver.h"
#include "framebuffer.h"

int fb_write(char *buf, uint32_t len) {
  uint32_t i;
  for(i = 0; i < len; i++) {
    fb_put_char(buf[i]);
  }
  return 0;
}

#ifdef USE_WRITE_DRIVER
int write(writable_t w, char *buf) {
  uint32_t i = 0;
  while(buf[i] != '\0') i += 1;
  return w(buf, i);
}
#endif /* USE_WRITE_DRIVER */
