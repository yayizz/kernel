#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__linux__)
#error "You are not using a cross-complier, you will mos certainly run into trouble"
#endif

#if !defined(__i386__)
#error "this tutorial needs to be compiled with a ix86-elf complier"
#endif

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *pTerminal_buffer;

/* VGA TEXT COLOR CONSTANTS */

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
VGA_COLOR_WHITE = 15,
};


static inline uint8_t vga_entry_color(enum vga_color foreGround,enum vga_color backGround)
{
    return foreGround | backGround << 4; // ForeGround bits are 8-11
                                          // BackGround bits are 12-14
}

static inline uint16_t vga_entry(uint8_t uc,uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t len(const char* pStr)
{
    size_t len = 0;
    while (pStr[len])
        len++;
    return len;
}


void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_GREEN,VGA_COLOR_BLACK);
    pTerminal_buffer = (uint16_t*) 0xB8000;
    for(size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            *(pTerminal_buffer + index) = vga_entry(' ',terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_put_entry_at(char c,uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    pTerminal_buffer[index] = vga_entry(c,color);
}

void terminal_putchar(char c)
{
    if(c == '\n'){
        ++terminal_row;
        terminal_column = 0;
    }
    else {

    
    terminal_put_entry_at(c,terminal_color,terminal_column,terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if(++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
    }
    }
}
void terminal_write(const char* pData,size_t size)
{
    for(size_t i = 0; i < size;i++)
    {
        terminal_putchar(pData[i]);
    }
}
void terminal_putstring(const char *pData)
{
    terminal_write(pData,len(pData));
}

void kernel_main(void)
{
    terminal_initialize();

    terminal_putstring("Hello, Kernel World!\n");

    terminal_putstring("I made it MAMA!\n");

}
