#include <stdint.h>

#define VIDEO_MEM 0xb8000
#define JSON_ADDR 0x9000
#define JOINER_ADDR 0x5000
#define SYSTEM_JSON_CHECKSUM 0xABCD1234

// --- HARDWARE ABSTRACTION LAYER (HAL) ---

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

static inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    asm volatile ( "inw %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

// --- DISK DRIVER (ATA PIO) ---

void ata_read_sector(uint32_t lba, uint16_t* buffer) {
    outb(0x1F2, 1);
    outb(0x1F3, (uint8_t)lba);
    outb(0x1F4, (uint8_t)(lba >> 8));
    outb(0x1F5, (uint8_t)(lba >> 16));
    outb(0x1F6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1F7, 0x20); // Command: Read

    while ((inb(0x1F7) & 0x08) == 0); // Wait for Data Request bit

    for (int i = 0; i < 256; i++) {
        buffer[i] = inw(0x1F0);
    }
}

// --- SYSTEM CORE ---

void print_string(char* str) {
    static int cursor = 0;
    volatile char* vga = (volatile char*)VIDEO_MEM;
    for (int i = 0; str[i] != '\0'; i++) {
        vga[cursor++] = str[i];
        vga[cursor++] = 0x07; 
    }
}

void drop_disk() {
    print_string("\n [!!] INTEGRITY FAILURE: VOID OF NOTHINGNESS ");
    outb(0x1F2, 1);
    outb(0x1F3, 0); // Target LBA 0 (MBR)
    outb(0x1F4, 0);
    outb(0x1F5, 0);
    outb(0x1F6, 0xE0);
    outb(0x1F7, 0x30); // Command: Write

    for (int i = 0; i < 256; i++) {
        asm volatile ("outw %0, %1" : : "a"((uint16_t)0), "Nd"((uint16_t)0x1F0));
    }
    
    outb(0x1F7, 0x08); // Reset
    asm volatile("cli; hlt");
}

uint32_t verify_integrity(uint32_t* addr, int words) {
    uint32_t checksum = 0;
    for (int i = 0; i < words; i++) {
        checksum ^= addr[i];
    }
    return checksum;
}

void kmain() {
    print_string("VAC OS: HARDENED KERNEL LOADED\n");
    print_string("LEAD ARCHITECT: SHRIJIITH MAHESH\n");

    // 1. Pull the "Rules" (Sector 5)
    ata_read_sector(5, (uint16_t*)JSON_ADDR);
    
    // 2. The "Six Eyes" Check
    if (verify_integrity((uint32_t*)JSON_ADDR, 128) != SYSTEM_JSON_CHECKSUM) {
        drop_disk();
    }

    print_string("INTEGRITY OK. SYSTEM SECURE.\n");

    // 3. Pull the "Joiner" (Sector 6)
    print_string("LOADING JOINER.C AT 0x5000...\n");
    ata_read_sector(6, (uint16_t*)JOINER_ADDR);

    // 4. JUMP TO JOINER
    void (*joiner_start)() = (void (*)())JOINER_ADDR;
    joiner_start();

    while(1); 
}
