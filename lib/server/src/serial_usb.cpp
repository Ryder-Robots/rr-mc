#include <serial_usb.hpp>

using namespace rrobot;

void SerialUsb::begin(unsigned long baud) {
    Serial.begin(baud);

#ifdef MBED
    while (!Serial);
#endif
}

size_t SerialUsb::write(const uint8_t bf) { return Serial.write(bf); }

void SerialUsb::flush(void) { Serial.flush(); }

int SerialUsb::available(void) { return Serial.available(); }

uint8_t SerialUsb::read(void) { return Serial.read(); }