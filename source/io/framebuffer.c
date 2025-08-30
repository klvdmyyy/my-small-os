#include "framebuffer.h"
#include "io.h"

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

static uint32_t cursorX = 0;
static uint32_t cursorY = 0;

void fb_move_cursor(int x, int y) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((FB_INDEX(x, y) >> 8) & 0x00FF));
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, FB_INDEX(x, y) & 0x00FF);
}

void fb_set_cell(int x, int y, char c, uint8_t fg, uint8_t bg) {
  FRAMEBUFFER(x, y) = (c & 0xff) | ((bg & 0xf) << 12) | ((fg & 0xf) << 8);
}

void fb_update_cursor() {
  fb_move_cursor(cursorX, cursorY);
}

void fb_new_line() {
  cursorY = 0;
  if(++cursorX >= FB_ROW) {
    /* fb_scroll(); */
  } else {
    fb_update_cursor();
  }
}

void fb_put_regular_char(char c) {
  fb_set_cell(cursorX, cursorY, c, 0xF, 0x0);
  if(++cursorY >= FB_COL) {
    fb_new_line();
  } else {
    fb_update_cursor();
  }
}

void fb_put_char(char c) {
  switch(c) {
  case '\n':
    fb_new_line();
    break;
  default:
    fb_put_regular_char(c);
    break;
  }
}

void fb_clear() {
  int i, j;
  for (i = 0; i < FB_ROW; i++) {
    for (j = 0; j < FB_COL; j++) {
      fb_set_cell(i, j, ' ', 0xf, 0x0);
    }
  }
}
