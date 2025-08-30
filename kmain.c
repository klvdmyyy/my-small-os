#include "framebuffer.h"
#include "driver.h"

void kernel_main() {
  // Framebuffer initializing.
  fb_clear();
  fb_move_cursor(0, 0);
  write(framebuffer, "Hello, from Kernel!");
  while(1);
}
