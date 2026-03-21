#include <stdint.h>

#define VIDEO_MEM 0xb8000
#define JSON_ADDR 0x9000
#define SYSTEM_JSON_CHECKSUM 0xABCD1234

// Direct I/O to talk to the Lenovo hardware
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

void print_string(char* str) {
    static int cursor = 0;
    volatile char* vga = (volatile char*)VIDEO_MEM;
    for (int i = 0; str[i] != '\0'; i++) {
        vga[cursor++] = str[i];
        vga[cursor++] = 0x07; // Gray text on Black
    }
}

void drop_disk() {
    print_string("\n[CRITICAL] ATTACK DETECTED. DROPPING DISK...");
    outb(0x1F7, 0x08); // ATA Software Reset Command
    asm volatile("cli; hlt"); // Total System Lock
}

uint32_t verify_integrity(uint32_t* addr, int words) {
    uint32_t checksum = 0;
    for (int i = 0; i < words; i++) {
        checksum ^= addr[i]; // Simple XOR DNA check
    }
    return checksum;
}

void kmain() {
    print_string("VAC OS: HARDENED KERNEL LOADED\n");
    print_string("LEAD ARCHITECT: SHRIJIITH MAHESH\n");

    // Simulate reading Sector 5 (In a real kernel, you'd call an ATA driver)
    uint32_t* system_json = (uint32_t*)JSON_ADDR;
    
    if (verify_integrity(system_json, 128) != SYSTEM_JSON_CHECKSUM) {
        print_string("INTEGRITY FAILURE: SYSTEM.JSON TAMPERED!\n");
        drop_disk();
    }

    print_string("INTEGRITY OK. SYSTEM SECURE.");
    while(1); // Keep the CPU alive
}
