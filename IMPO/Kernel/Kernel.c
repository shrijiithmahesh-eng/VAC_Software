/* * VAC OS: HARDENED KERNEL 
 * Lead Engineer: Shrijiith Mahesh (kechu10)
 * Status: HIGH SECURITY / MARS TERRAFORMING READY
 */

#include "stdint.h"

// The "Golden Key" - This is the sum of all bytes in a perfect System.json
// If the file changes by even 1 bit, this check will fail!
#define SYSTEM_JSON_CHECKSUM 0xABCD1234 
#define DRIVER_ADDR 0x10000
#define JOINER_ADDR 0x20000
#define JSON_ADDR   0x9000

// --- PROTOTYPES ---
void kernel_panic(char* message);
uint32_t verify_integrity(uint32_t address, int size);
void print_string(char* str);
void clear_screen();

// --- THE HARDENED ENGINE ---

void kmain() {
    // 1. Setup the Hardware Rules (GDT) and Reflexes (IDT)
    setup_gdt(); 
    setup_idt();

    clear_screen();
    print_string("VAC OS: [HARDENED MODE ACTIVE]\n");
    print_string("------------------------------\n");

    // 2. Accessing the Disk Controller (Port 0x1F7)
    print_string("Targeting Sector 5 (System.json)... ");
    
    if (ata_read_sectors(JSON_ADDR, 1, 5)) {
        print_string("READ OK.\n");

        // SECURITY CHECK: Verify the DNA of the file
        print_string("Verifying Integrity... ");
        if (verify_integrity(JSON_ADDR, 512) == SYSTEM_JSON_CHECKSUM) {
            print_string("[VERIFIED]\n");
        } else {
            kernel_panic("CRITICAL: SYSTEM.JSON TAMPERED OR CORRUPT!");
        }
    } else {
        kernel_panic("DISK_READ_FAILURE: SECTOR_MISSALIGNED");
    }

    // 3. Loading the Hardware Abstraction Layer (The Hand)
    print_string("Loading Driver.c at 0x10000... ");
    load_driver("driver.c", DRIVER_ADDR);
    print_string("[OK]\n");

    // 4. Loading the Module Linker (The Synapse)
    print_string("Starting Joiner.c at 0x20000... ");
    load_join("joiner.c", JOINER_ADDR);
    
    print_string("\n[SUCCESS] INIT SYSTEM READY.\n");
    print_string("STARTING LOGIN PROTOCOL...\n");
}

// --- SECURITY TOOLS ---

// The Panic Protocol: Completely halts the CPU to protect data
void kernel_panic(char* message) {
    clear_screen();
    print_string("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    print_string("!!           KERNEL PANIC             !!\n");
    print_string("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n");
    print_string("REASON: ");
    print_string(message);
    print_string("\n\nSYSTEM HALTED TO PROTECT VAULT.");
    
    // Disable interrupts and stop the CPU
    asm volatile("cli; hlt"); 
}

// A simple Polynomial (P) Checksum to verify data
uint32_t verify_integrity(uint32_t address, int size) {
    uint32_t checksum = 0;
    unsigned char* ptr = (unsigned char*)address;
    
    for(int i = 0; i < size; i++) {
        checksum += ptr[i];
    }
    return checksum;
}
