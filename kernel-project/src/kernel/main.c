
#include "print.h"

void kernel_main(void) {
    clear();
    set_color(0x0A, 0x00);
    print_str("Welcome to 64-bit kernel\n");

    while (1) {
        __asm__("hlt");
    }
}
