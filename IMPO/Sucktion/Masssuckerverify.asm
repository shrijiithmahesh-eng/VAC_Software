; VAC OS: FINAL TORNADO EVASION INTEGRATION
; Input: EAX = Distance (cm)

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
