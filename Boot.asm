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
int 0x10        ; Print it
