#include "framebuffer.h"

void kernel_main() {
  fb_clear();
  fb_move_cursor(0, 0);
  while(true);
}
