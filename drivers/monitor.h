#ifndef MONITOR_H_
#define MONITOR_H_

#include "common.h"

#define VGA_ADDRESS 0xB8000
#define SCREEN_HEIGHT 25
#define SCREEN_WIDTH 80

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

#define WHITE_ON_BLACK 0x0f


void monitor_init(void);
void monitor_putchar(const char c);

void monitor_clear(void);

void monitor_write(const char *pStr);

void monitor_config(void);



enum vga_color {

VGA_COLOR_BLACK = 0,
VGA_COLOR_BLUE = 1,
VGA_COLOR_GREEN = 2,
VGA_COLOR_CYAN = 3,
VGA_COLOR_RED = 4,
VGA_COLOR_MAGENTA = 5,
VGA_COLOR_BROWN = 6,
VGA_COLOR_LGHT_GREY = 7,
VGA_COLOR_DRK_GREY = 8,
VGA_COLOR_LGHT_BLUE = 9,
VGA_COLOR_LGHT_GREEN = 10,
VGA_COLOR_LGHT_CYAN = 11,
VGA_COLOR_LGHT_RED = 12,
VGA_COLOR_PINK = 13,
VGA_COLOR_YELLOW = 14,
VGA_COLOR_WHITE = 15
};

#endif // MONITOR_H_
