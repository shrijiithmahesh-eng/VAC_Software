

; VAC OS: FINAL TORNADO EVASION INTEGRATION
; Input: EAX = Distance from tornado center

PROXIMITY_THRESHOLD equ 92
DURATION_MULTIPLIER equ 10
THRUSTER_PORT       equ 0x3F
THRUSTER_ENGAGE     equ 0x01

check_vortex_proximity:
    test eax, eax
    jz   emergency_stop
    cmp  eax, PROXIMITY_THRESHOLD
    jle  start_evasion
    ret

start_evasion:
    call calculate_thrust_duration  ; Result returned in EBX
    call execute_thrust             ; EBX = burn duration
    ret

; Input:  EAX = current distance from tornado center
; Output: EBX = calculated burn duration (ticks)
calculate_thrust_duration:
    mov  ebx, PROXIMITY_THRESHOLD
    sub  ebx, eax
    imul ebx, DURATION_MULTIPLIER
    ret                             ; EBX = burn time

; Input: EBX = burn duration
execute_thrust:
    cli                     ; Minimize interrupt-disabled window
    mov  dx, THRUSTER_PORT
    mov  al, THRUSTER_ENGAGE
    out  dx, al
    sti

    ; TODO (Vishwashwar/Shriram): implement delay loop using EBX here
    ; EBX holds burn duration in ticks — do NOT clobber it before the loop
    ret
