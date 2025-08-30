#include <io/driver.h>
#include <io/framebuffer.h>

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

void kernel_main() {
  // Framebuffer initializing.
  fb_clear();
  fb_move_cursor(0, 0);

  write(framebuffer, my_small_os_header);

  while (1)
    ;
}
