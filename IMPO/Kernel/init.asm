; =================================================
; VAC OS INIT SYSTEM (PID 1)
; Designed by: Shrijiith Mahesh
; =================================================

section .text
global _start

_start:
    ; 1. Display the Creator's Mark
    mov rsi, msg_welcome
    call print_string

    ; 2. Initialize the Laser Hardware (Port 0x05)
    mov dx, 0x05        ; The Steel Container Link
    in al, dx           ; Check status
    cmp al, 0xFF        ; Is it connected?
    je .hardware_ready

.panic:
    mov rsi, msg_error
    call print_string
    hlt                 ; Stop the CPU if link fails

.hardware_ready:
    ; 3. The "Idle" Loop - Keeping the OS Alive
    jmp .hardware_ready

section .data
    msg_welcome db "Vac OS v1.0 - Designed by Shrijiith", 0xA, 0
    msg_error   db "CRITICAL: STEEL CONTAINER LINK FAILED!", 0xA, 0
