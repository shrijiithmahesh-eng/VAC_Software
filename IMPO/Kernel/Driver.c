// Shedon OS - Driver Core v1.0
// Author: Shrijiith ($12083USR)


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
    int key = hardware_bus_read();
    if (key == PIN_UP || key == PIN_LEFT || key == PIN_RIGHT) {
        return key; // Valid input
    } else {
        system_shutdown(); // Rule: Any other key = Shutdown
    }
}
