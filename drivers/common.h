#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void outb(unsigned short port,unsigned char value);
unsigned char inb(unsigned short port);
unsigned short inw(unsigned short port);

int len(const char *pStr);

#endif // COMMON_H_
