#include "driver.h"
#include "framebuffer.h"

static volatile int col = 1;
static volatile int row = 1;

int fb_write(char *buf, uint32_t len) {
  uint32_t i;
  for(i = 0; i < len; i++) {
    if (row == FB_ROW) {
      return 1;
    }
    if (col == FB_COL) {
      col = 1;
      row += 1;
    }
    fb_set_cell(col-1, row-1, buf[i], 0xf, 0x0);
    fb_move_cursor(col, row-1);
    col += 1;
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
