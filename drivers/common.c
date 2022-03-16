#include "common.h"

/* Write a byte to the specified port */
void outb(uint16_t port,uint8_t data)
{
    asm volatile("outb %0, %1" : : "a" (data),"Nd" (port));
}
/* Take one byte input from specified port */

unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

/* take two byte input from specified port */

unsigned short inw(unsigned short port)
{
    unsigned short ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

int len(const char *pStr)
{
    int len = 0;
    while(pStr[len])
        len++;
    return len;
}
