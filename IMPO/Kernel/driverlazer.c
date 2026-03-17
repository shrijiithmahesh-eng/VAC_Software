#define STEEL_CONTAINER_LINK 0x05 
#define RAM_MAX_MB 2048 // Back to the 2GB Rule!

void fire_laser(int intensity) {
    // 1. Check RAM 
    if (get_mem_usage() > RAM_MAX_MB) {
        log_event("BUFFER OVERFLOW");
        system_shutdown(); // Rule #1 Enforcement
        return;
    }

    // 2. Check Connection to the Steel Container
    // This is the physical link to port 0x05
    if (!check_link(STEEL_CONTAINER_LINK)) {
        log_event("HARDWARE_DISCONNECT_ERROR");
        return;
    }

    // 3. Execute the Melt
    // START_MELT is the signal sent to the hardware bus
    send_signal(STEEL_CONTAINER_LINK, START_MELT);
    log_event("LASER_ACTIVE: MELTING_ICE");
}
