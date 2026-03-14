// SSH Is an open-source protocol used to remortely connect to machines.
// We don't claim SSH is ours.
//It was created by daztucker.
// We are using it to connect from earth to mars using a ssh server.
#include "time_patch.c"
#define SSH.CONNECT
void SSH.CONNECT() {
int mars_socket = socket(AF_INET, SOCK_STREAM, 0);
    apply_latency_buffer(mars_socket); // From time_patch.c

    // 2. Point to the Martian IP 
    struct sockaddr_in mars_addr;
    mars_addr.sin_family = AF_INET;
    mars_addr.sin_port = htons(22); // The Sacred Port
    inet_pton(AF_INET, "192.168.MARS.1", &mars_addr.sin_addr);

    // 3. Initiate the Long-Distance Handshake
    if (connect(mars_socket, (struct sockaddr *)&mars_addr, sizeof(mars_addr)) < 0) {
        log_event("MARS_UNREACHABLE_IN_DARKNESS");
        return;
    }

    // 4. Secure the Tunnel 
  start_ssh_handshake(mars_socket);
}
