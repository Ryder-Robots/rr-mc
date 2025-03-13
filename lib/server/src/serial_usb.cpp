#include <serial_usb.hpp>

using namespace rrobot;

void SerialUsb::begin(unsigned long baud) {
    Serial.begin(baud);
}

size_t SerialUsb::write(const uint8_t* bf, size_t sz) {
    return Serial.write(bf, sz);
}

void SerialUsb::flush(void) {
    Serial.flush();
}

int  SerialUsb::available(void) {
    return Serial.available();
}

uint8_t* SerialUsb::read(void) {
    uint8_t* buf = reinterpret_cast<uint8_t*>(malloc(_mxbuf));
    int i = 0;
    uint8_t c = 0;
    while (c != _tm && i < _mxbuf) {
        c = Serial.read();
        buf[i++] = c;
    }

    return buf;
}