// This is the main entry point from the Bootloader
void kmain() {
    // 1. Clear the screen (1900s style - Black background)
    clear_screen();

    // 2. Print the HackMe Welcome Message
    print_string("VAC KERNEL V1.0 ONLINE\n");
    // 3. The Big Jump: Load the JSON settings
    load_system_rules("System.json");
    load_drivers1("driver.c")
    load_join("Joiner.c")
    load_driverlazer("driverlazer.c")
    // 4. Infinite Loop (Keep the system running)
    while(1) {
        // Stay alive!
    }
}

void print_string(char* text) {
    // This talks to the Video Memory at 0xB8000
    // (The 1900s way to show text!)
}
