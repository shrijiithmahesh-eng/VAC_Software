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
times 510-($-$$) db 0   ; Fill with 0s until byte 510
dw 0xAA55               ; The Magic Boot Signature (Bytes 511 and 512)
