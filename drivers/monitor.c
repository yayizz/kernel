#include "monitor.h"

static  uint16_t *pMonitor;
static uint8_t attr;
static int row,col;

static inline uint8_t entry_color(enum vga_color fg,enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t entry(uint8_t c, uint8_t color){

    return (uint16_t) c | (uint16_t) color << 8;
}

static void roll()
{
    for(int i = 0; i< SCREEN_WIDTH * SCREEN_HEIGHT/2;i++)
    {
        pMonitor[i] = pMonitor[i + SCREEN_HEIGHT/2*SCREEN_WIDTH];
        pMonitor[i+SCREEN_HEIGHT/2*SCREEN_WIDTH] = entry(' ',entry_color(VGA_COLOR_BLACK,VGA_COLOR_BLACK));
    }
    col = 0;
    row = SCREEN_HEIGHT/2 ;
}


static void move_cursor(void){

    uint16_t cursor = SCREEN_WIDTH * row + col;

    outb(0x3D4,14);
    outb(0X3D5,cursor >> 8);
    outb(0x3D4,15);
    outb(0x3D5,cursor);


}
static void cursor_init()
{
    outb(0x3D4,0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 0);

    outb(0x3D4,0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | SCREEN_HEIGHT);

    move_cursor();
}


void monitor_init(void)
{
     pMonitor = (uint16_t *) VGA_ADDRESS;

     attr = 0;

     monitor_clear();

     cursor_init();

}


void monitor_putchar(const char c)
{
    if(!attr)
    {
        attr = entry_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK);
    }

    if(c == '\n')
    {
        if(++row >= SCREEN_HEIGHT)
        {
            roll();
        }
        col = 0;
    }

    else {

    int idx = row * SCREEN_WIDTH + col;
    pMonitor[idx] = entry(c,attr);
    if(++col >= SCREEN_WIDTH)
    {
        col = 0;
        if(++row >= SCREEN_HEIGHT)
        {
            roll();
        }
    }

    }
    move_cursor();
    
}

void monitor_clear(void)
{
    for(int i = 0;i < SCREEN_WIDTH*SCREEN_HEIGHT;i++)
    {
        pMonitor[i] = entry(' ',entry_color(VGA_COLOR_WHITE,VGA_COLOR_BLACK));

    }
    row = 0;
    col = 0;
    move_cursor();
}

void monitor_write(const char *pStr)
{
    int l = len(pStr);

    for(int i = 0; i < l;i++)
    {
        monitor_putchar(pStr[i]);
    }
}
