[bits 32]
LoadGDT:
    lgdt [esp + 4]
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov ax,0x18
    mov gs,ax
    ret
GLOBAL LoadGDT
;;// TODO MAKE IT COMPETIBLE WITH KERNEL

