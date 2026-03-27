#define PIN_UP 0x01
#define PIN_LEFT 0x02
#define PIN_RIGHT 0x03
#define PIN_PWR 0x04
void init_vacuum_hardware() {
    // Check Rules.json for RAM limits before starting
    if (get_mem_usage() > 2048) {
        system_shutdown(); // Rule #1 Enforcement
    }
}


int read_input() {
    int key = hardware_bus_read(); // Grab the hex from Port 0x60
    
    if (key == 0) {
        return 0; // No key pressed, keep the loop spinning
    }

    // REMOVED: system_shutdown() on unknown keys.
    // ADDED: Universal Return.
    
    return key; // Every key is now a "Valid Input"
}

void process_text() {
    int key = read_input();
    if (key != 0) {
        // This is where you map the Hex to "Hello" 
        printf("Key Pressed: 0x%02X\n", key); 
    }
}
