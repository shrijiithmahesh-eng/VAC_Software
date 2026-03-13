;The login
_start:
section .data
    prompt db " [KERNEL]: Login ", 0
    promt db "VAC OS"
    prompt_len equ $ - prompt
    
    ; THE HIGH-ENTROPY KEY
    master_key db "#######_####### #", 0
    key_len equ $ - master_key
; I hid the key , so the password isn't #########_######    
    success_msg db 10, " [KERNEL]: WELCOME", 10, 0
    fail_msg db 10, "[KERNEL]: ACCESS DENIED.", 10, 0

section .bss
    input_buffer resb 64        ; Reserve space for the long password

section .text
    global _start

_start:
    ; 1. Print the Prompt
    mov rax, 1                  ; sys_write
    mov rdi, 1                  ; stdout
    mov rsi, prompt
    mov rdx, prompt_len
    syscall

    ; 2. Read User Input
    mov rax, 0                  ; sys_read
    mov rdi, 0                  ; stdin
    mov rsi, input_buffer
    mov rdx, 64
    syscall

    ; 3. Compare Strings (The "Steel Link" Check)
    mov rsi, master_key
    mov rdi, input_buffer
    mov rcx, key_len            ; Check character by character
    repe cmpsb                  ; Repeat while equal
    jne .access_denied          ; If not equal, kick them out

.access_granted:
    mov rax, 1
    mov rdi, 1
    mov rsi, success_msg
    mov rdx, 52
    syscall
    jmp .exit

.access_denied:
    mov rax, 1
    mov rdi, 1
    mov rsi, fail_msg
    mov rdx, 38
    syscall

.exit:
    mov rax, 60                 ; sys_exit
    xor rdi, rdi
    syscall
