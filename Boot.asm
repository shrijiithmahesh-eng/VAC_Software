[bits 16]
[org 0x7c00]  
; --- The Start of Project VAC ---
start:
  mov ah, 0x0E  ; Tell BIOS we want to print a character
int 0x10        ; Call the Video Interrupt

mov al, 'V'     ; Load 'V'
int 0x10        ; Print it

mov al, 'a'     ; Load 'a'
int 0x10        ; Print it

mov al, 'c'     ; Load 'c'
int 0x10         ;print it


load_kernel:
    mov ah, 0x02    ; BIOS 'Read Disk' function
    mov al, 1       ; Read 1 sector (The Kernel)
    mov ch, 0       ; Cylinder 0
    mov dh, 0       ; Head 0
    mov cl, 2       ; Sector 2 (Right after the Bootloader!)
    mov bx, 0x1000  ; Memory address to drop the Kernel
    mov es, bx
    xor bx, bx
    int 0x13        ; DISK INTERRUPT!

    jmp 0x1000:0000 ; THE JUMP TO THE KERNEL!
dw 0xAA55               ; The Magic Boot Signature (Bytes 511 and 512)
