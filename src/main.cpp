#include <main.hpp>

using namespace rrobot;

Crc32 crc;
Ld001ControllerFactory fact = Ld001ControllerFactory();
SerialUsb Serial;
RrMultiWii* multiWii;

void setup() {
    multiWii = new RrMultiWii(crc, Serial, fact);
    multiWii->setup();
}

void teardown() {
    multiWii->tearDown();
}

void loop() {
    multiWii->execute();
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