
#include "print.h"

static unsigned short *vga = (unsigned short *) 0xb8000;
static int cursor = 0;
static char color = 0x07;

void clear(void) {
    for (int i = 0; i < 80 * 25; i++) {
        vga[i] = (color << 8) | ' ';
    }
    cursor = 0;
}

void set_color(char fg, char bg) {
    color = (bg << 4) | (fg & 0x0F);
}

void print_str(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            cursor = (cursor / 80 + 1) * 80;
            continue;
        }
        vga[cursor++] = (color << 8) | str[i];
    }
}
