[bits 16]           ; Start in 16-bit Real Mode (Legacy)
[org 0x7c00]  

start:
    ; --- 1. Print 'Vac' in 16-bit mode before we switch ---
    mov ah, 0x0E
    mov al, 'V'
    int 0x10
    mov al, 'a'
    int 0x10
    mov al, 'c'
    int 0x10

    ; --- 2. Switch to 32-bit Protected Mode ---
    cli                     ; Clear Interrupts (BIOS can't help us anymore)
    lgdt [gdt_descriptor]   ; Load the Global Descriptor Table (The 32-bit rules)
    mov eax, cr0
    or eax, 0x1             ; Set the Protected Mode bit
    mov cr0, eax

    jmp CODE_SEG:init_32bit ; "Far Jump" to flush the CPU pipeline

[bits 32]                   ; Now we are in 32-bit mode!
init_32bit:
    mov ax, DATA_SEG        ; Update all segment registers
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; --- 3. Print '32' directly to Video Memory (0xB8000) ---
    mov edi, 0xB8000        ; Starting address of VGA memory
    mov [edi], word 0x0F33  ; '3' in White text on Black background
    mov [edi+2], word 0x0F32; '2' in White text on Black background

    jmp $                   ; Stay here (Hang)

; --- GDT (Global Descriptor Table) ---
; This tells the CPU how to handle memory in 32-bit mode
gdt_start:
    dq 0x0                  ; Null descriptor
gdt_code:                   ; Code segment descriptor
    dw 0xffff, 0x0, 0x9a, 0xcf, 0x0
gdt_data:                   ; Data segment descriptor
    dw 0xffff, 0x0, 0x92, 0xcf, 0x0
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

times 510-($-$$) db 0  
dw 0xAA55

