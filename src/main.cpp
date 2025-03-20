#include <main.hpp>

using namespace rrobot;

Crc32 crc;
Ld001ControllerFactory fact = Ld001ControllerFactory();
SerialUsb serialUsb = SerialUsb();
RrMultiWii multiWii = RrMultiWii(crc, serialUsb, fact);

void setup() {
    serialUsb.begin(SERIAL_BAUD);
    multiWii.setup();
}

/**
 * @fn teardown
 * @brief
 * teardown process by using teardown method
 */
void teardown() { multiWii.tearDown(); }

void loop() {
    delay(MAIN_LOOP_DELAY);
    multiWii.execute();    
}

#ifdef NATIVE
/**
 * @fn main
 * @brief
 * main method added so that code can be compiled using native environment with library ArduinoFake
 */
int main() {
    setup();
    while (1) {
        loop();
    }
    return 0;
}

#endif