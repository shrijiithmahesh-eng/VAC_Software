; VAC OS: FINAL TORNADO EVASION INTEGRATION
; Input: EAX = Distance from Tornado center

check_vortex_proximity:
    cmp eax, 0          
    je emergency_stop   

    cmp eax, 92         
    jle start_evasion   ; Match found: Initiate Steel Protocol
    ret                 

start_evasion:
    cli                 ; LOCK THE CPU: No distractions during evasion
    call calculate_thrust_duration ; Calculate EAX (duration) first!
    call execute_thrust            ; Fire the thrusters using the calculated EAX
    sti                 ; UNLOCK THE CPU: Resume standard Mars operations
    ret

execute_thrust:
    mov dx, 0x3F        ; Thruster Port
    mov al, 0x01        ; Engage Command
    out dx, al          ; PHYSICAL ACTION TAKEN
    
    ; Note: The Logic Team (Vishwashwar/Shriram) needs to 
    ; implement a delay loop here based on the value in EAX.
    ret

calculate_thrust_duration:
    mov ebx, 92         
    sub ebx, eax        
    mov ecx, 10         
    imul ebx, ecx       
    mov eax, ebx        ; EAX now holds the "Burn Time"
    ret
