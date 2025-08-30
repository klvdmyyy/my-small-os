#pragma once

#include "types.h"

typedef uint16_t fb_t;

#define FB_BASE ((fb_t *)0x00b8000)
#define FB_COL 80
#define FB_ROW 25

#define FB_INDEX(x, y) (FB_ROW * y + x)
#define FRAMEBUFFER(x, y) (*(FB_BASE + FB_INDEX(x, y)))

void fb_move_cursor(int x, int y);
void fb_set_cell(int x, int y, char c, uint8_t fg, uint8_t bg);
void fb_clear();
