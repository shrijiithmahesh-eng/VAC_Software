; VAC OS: FINAL TORNADO EVASION INTEGRATION
; Input: EAX = Distance (cm)
; --- ADD THIS BACK AT THE TOP ---
check_vortex_proximity:
    test eax, eax           ; Check if distance is 0
    jz   emergency_stop     ; If distance is 0, the tornado is ON TOP of us!
    
    cmp  eax, PROXIMITY_THRESHOLD
    jle  start_evasion      ; If <= 92cm, start the math
    ret                     ; Otherwise, we are safe (for now)

start_evasion:
    call calculate_thrust_duration
    call execute_thrust
    ret

emergency_stop:
    cli                     ; Stop all interrupts
    mov al, 0xFF            ; Diagnostic port signal
    out 0x80, al

    ; --- BIOS Print "this the end" ---
    mov ah, 0x0E            ; BIOS Teletype function
    
    mov al, 't'
    int 0x10                ; Print 't'
    mov al, 'h'
    int 0x10                ; Print 'h'
    mov al, 'i'
    int 0x10
    mov al, 's'
    int 0x10
    mov al, ' '             ; Space character
    int 0x10
    mov al, 't'
    int 0x10
    mov al, 'h'
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, ' '
    int 0x10
    mov al, 'e'
    int 0x10
    mov al, 'n'
    int 0x10
    mov al, 'd'
    int 0x10

    hlt                     ; Final system halt. Mission Over.
PROXIMITY_THRESHOLD equ 92
; 0.333 seconds = 333 milliseconds. 
; So, Burn Time (ms) = (92 - distance) * 333
MS_MULTIPLIER       equ 333 
THRUSTER_PORT       equ 0x3F

calculate_thrust_duration:
    mov  ebx, PROXIMITY_THRESHOLD
    sub  ebx, eax           ; EBX = distance delta in cm
    imul ebx, MS_MULTIPLIER ; EBX = total burn time in MILLISECONDS
    ret

execute_thrust:
    cli
    mov  dx, THRUSTER_PORT
    mov  al, 0x01
    out  dx, al             ; THRUSTERS ON

    ; Now we need a delay loop that accurately waits 1ms per EBX unit
.wait_ms:
    push ebx
    mov  ecx, 2500000       ; CALIBRATION: Adjust this for your Yoga 520 (2.5GHz-ish)
.inner_loop:
    dec  ecx
    jnz  .inner_loop        ; This loop should take exactly 1ms
    pop  ebx
    
    dec  ebx
    jnz  .wait_ms           ; Repeat for every millisecond in EBX

    mov  al, 0x00
    out  dx, al             ; THRUSTERS OFF
    sti
    ret
