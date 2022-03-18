[bits 32]
extern gp
gdt_flush:
    lgdt [gp]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ax, ss

    ret
GLOBAL gdt_flush
;;// TODO MAKE IT COMPETIBLE WITH KERNEL

