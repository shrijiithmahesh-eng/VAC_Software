; VAC OS: 32-BIT SHUTDOWN PROCEDURE
; Architect: Shrijiith Mahesh

[BITS 32]

section .text
global shutdown_sequence

VIDEO_MEMORY equ 0xB8000
WHITE_ON_BLACK equ 0x0F

shutdown_sequence:
    ; 1. Kill Thrusters immediately
    mov dx, 0x3F
    mov al, 0x00
    out dx, al

    ; 2. Print the Final Message to VGA Buffer
    mov esi, msg_final
    mov edi, VIDEO_MEMORY    ; Start at top-left of screen
    call print_string_32

    ; 3. Final Halt
    cli
    hlt

print_string_32:
    .loop:
        lodsb               ; Load byte from ESI into AL
        test al, al         ; Check for null terminator
        jz .done
        
        mov [edi], al       ; Write character
        mov [edi+1], byte WHITE_ON_BLACK ; Write color attribute
        add edi, 2          ; Move to next character cell (2 bytes per char)
        jmp .loop
    .done:
        ret

section .data
    msg_final db 'STATUS: DARKNESS. GOODBYE, CHENNAI. [MATH FAIL: 0.333s/cm]', 0
   
