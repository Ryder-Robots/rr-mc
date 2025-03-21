#include <serial_usb.hpp>

using namespace rrobot;

size_t SerialUsb::write(const uint8_t bf) { return Serial.write(bf); }

void SerialUsb::flush(void) { Serial.flush(); }

int SerialUsb::available(void) { return Serial.available(); }

uint8_t SerialUsb::read(void) { return Serial.read(); }