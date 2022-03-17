#ifndef GDT_H_
#define GDT_H_

#include "common.h"

struct GDT_ENTRY
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;


}__attribute__((packed));

typedef struct GDT_ENTRY GDT_ENTRY_T;


struct GDT_PTR
{
    uint16_t limit;
    uint32_t base;

}__attribute__((packed));

typedef struct GDT_PTR GDT_PTR_T;

GDT_ENTRY_T gdt[3];
GDT_PTR_T gp;

extern void gdt_flush();

#endif // GDT_H_
