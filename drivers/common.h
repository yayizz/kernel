#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

void outb(uint16_t port,uint8_t  value);
uint8_t inb(uint16_t port);
unsigned short inw(unsigned short port);

int len(const char *pStr);

#endif // COMMON_H_
