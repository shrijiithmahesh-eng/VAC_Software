#define STEEL_CONTAINER_LINK 0x05 
#define RAM_MAX_MB 2048 // Back to the 2GB Rule!

void fire_laser(int intensity) {
    // 1. Check RAM 
    if (check_ram() > RAM_MAX_MB) {
        log_event("BUFFER OVERFLOW");
        system_shutdown(" RAM LIMIT EXCEEDED");
        return;
    }

    // 2. Check Connection to the Steel Container
    if (!check_link(STEEL_CONTAINER_LINK)) {
        log_event("HARDWARE_DISCONNECT_ERROR");
        return;
    }

    // 3. Execute the Melt
    send_signal(STEEL_CONTAINER_LINK, START_MELT);
    log_event("LASER_ACTIVE: MELTING_ICE");
} //END
