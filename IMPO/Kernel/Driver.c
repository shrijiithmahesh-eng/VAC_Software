#define PIN_UP 0x01
#define PIN_LEFT 0x02
#define PIN_RIGHT 0x03
#define PIN_PWR 0x04
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
    if (key == 0) return;

    switch(key) {
        case PIN_UP:
            print_string("THRUSTERS: FORWARD\n");
            break;
        case PIN_PWR:
            print_string("VAC OS: ENTERING STANDBY\n");
            break;
        default:
            // The Universal Return at work:
            print_string("LOG: Unmapped Telemetry 0x%02X\n", key);
    }
}
