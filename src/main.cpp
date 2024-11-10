#include <rr-mc.h>

using namespace rrobot;
auto msp   = MspHeartBeat(MAV_MODE_PREFLIGHT, 0, MAV_STATE_STANDBY);
auto timer = timer_create_default();

bool sendHeartbeat(void *) {
    uint8_t *packet = msp.serialize();

    for (size_t i = 0; i < msp.getPacketSz(); i++) {
        SERIAL_PORT.write(packet[i]);
    }

    free(packet);
    return true;
}


void setup() {
    // Initilize pins and send back armed response.
    SERIAL_PORT.begin(SERIAL_BAUD);
    timer.every(1000, sendHeartbeat);
}

void loop() {
  timer.tick();
}