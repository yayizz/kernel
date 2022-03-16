#include "kernel.h"

#if defined(__linux__)
#error "You are not using a cross-complier, you will mos certainly run into trouble"
#endif

#if !defined(__i386__)
#error "this tutorial needs to be compiled with a ix86-elf complier"
#endif



void kernel_main(void)
{
    monitor_init();

    monitor_write("hello\n");

    monitor_write("is anyone home\n");

    for(int i = 0;i<500000000;i++);
    monitor_clear();
}
