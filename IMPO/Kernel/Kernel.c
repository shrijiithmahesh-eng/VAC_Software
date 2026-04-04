void kmain() {
    print_string("VAC OS: V3 SOVEREIGN CORE LOADED\n");

    // 1. Pull & Verify Rules (Sector 5)
    ata_read_sector(5, (uint16_t*)JSON_ADDR);
    if (verify_integrity((uint32_t*)JSON_ADDR, 376) != SYSTEM_JSON_CHECKSUM) {
        drop_disk();
    }

    // 2. Pull & Verify Joiner (Sector 6) - NEW PROTECTION
    print_string("VERIFYING JOINER DNA...\n");
    ata_read_sector(6, (uint16_t*)JOINER_ADDR);
    
    // We assume the Joiner has its own expected checksum (e.g., 0x55667788)
    if (verify_integrity((uint32_t*)JOINER_ADDR, 128) != 0x55667788) {
        print_string("\n [!!] JOINER CORRUPTION DETECTED ");
        drop_disk();
    }

    // 3. SECURE JUMP
    void (*joiner_start)() = (void (*)())JOINER_ADDR;
    joiner_start();
}
