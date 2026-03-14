void kmain() {
     setup_gdt(); 

    // 2. Setup Interrupts (The Reflexes)
    setup_idt();

    clear_screen();
    print_string("VAC OS: HARDENED MODE ACTIVE\n");

   // THIS IS THE FORGOTTEN ENGINE
    // 1. Talk to Disk Controller (Port 0x1F7)
    // 2. Read 'System.json' into a buffer at 0x9000
    print_string("Accessing System.json... ");
    if (ata_read_sectors(0x9000, 1, 5)) { // (Target, StartSector, Count)
        print_string("LOADED.\n");
    } else {
        print_string("SECTOR_FAILURE.\n");
        log_event("SECTORS-MISSALYGYN");
    }
}

void load_driverlazer(char* filename) {
    print_string("Initializing ram.. ");
    // We map the Laser Driver to a specific high-memory address
    ata_read_sectors(0x50000, 10, 20); 
    // 1. Load the Hardware Abstraction Layer
    // We place driver.c at 0x10000 (The 'Hand' Sector)
    load_driver("driver.c", 0x10000);

    // 2. Load the Module Linker
    // We place joiner.c at 0x20000 (The 'Synapse' Sector)
    load_join("joiner.c", 0x20000);
    print_string("kahaha Joiner.c has started..\n");
}
