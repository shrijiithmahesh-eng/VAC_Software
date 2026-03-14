/* VAC OS: OPENSSH LATENCY PATCH */
#define MARS_LATENCY_BUFFER 1200 // 20 minutes in seconds

void adjust_ssh_timeouts() {
    // Override the "Modern" 2-minute timeout
    current_ssh_session->timeout = MARS_LATENCY_BUFFER;
    log_event("SSH_PROTOCOL");
}
