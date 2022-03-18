#ifndef KERNEL_H_
#define KERNEL_H_

#include "../drivers/common.h"
#include "../drivers/monitor.h"
#include "../drivers/gdt.h"

extern void gdt_install();

#endif // KERNEL_H_
