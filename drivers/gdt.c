#include "gdt.h"

/*
 * setup a descriptor in the Global Descriptor Table */
void gdt_set_gate(uint32_t num,uint32_t base, uint32_t limit,uint8_t access,uint8_t gran)
{
    /* Setup the descriptor base address */
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    /* Setup the descriptor limits */
    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    /* SET UP THE GRANULARİTY AND ACCESS FLAGS */

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

/* Should be called by kernel_main. This will setup the special GDT
 * pointer, set up the first 3 entries in our GDT, and then finally
 * call Load_GDT() in our assembler file in order to tell the
 * processor where the new GDT is and update the new segment registers */
void gdt_install()
{
    /* setup the GDT pointer and LİMİT */
    gp.limit = (sizeof(GDT_ENTRY_T)* 3) -1;
    gp.base = (uint32_t)&gdt;

    /* NULL descriptor */
    gdt_set_gate(0,0,0,0,0);

    /* the second entry is Code Segment.
     * The base address is 0, the limit is 4gb
     * it uses 4kb granularity, uses 32bit opcodes
     * and is a Code segment descriptor */
    gdt_set_gate(1,0,0XFFFFFFFF,0x9A,0xCF);
    /* third entry is Data Segment */
    gdt_set_gate(2,0,0xFFFFFFFF,0x92,0xCF);

    /* flush out the old gdt and install new changes */
    gdt_flush();
}
