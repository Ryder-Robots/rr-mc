#include <encoder.hpp>

using namespace rrobot;

uint16_t RrEncoder::decodeUint16(uint8_t* data, int& pos) {
    return (static_cast<uint16_t>(data[pos++]) << 8) | data[pos++];
}

// TODO: this needs to be completed.
uint32_t  RrEncoder::decodeUint32(uint8_t* data, int& pos) {
    return (uint32_t)data[pos++] << 24 |
           (uint32_t)data[pos++] << 16 |
           (uint32_t)data[pos++] << 8  |
           (uint32_t)data[pos++];
}

int RrEncoder::splitUint16(uint16_t value, uint8_t* data, int pos) {
    uint16_t encoded = htons(value);
    data[pos] = (encoded >> 8) & 0xFF;
    data[pos + 1] = encoded & 0xFF;
    return pos + 2;
}

int RrEncoder::splitUint32(uint32_t value, uint8_t *data, int pos) {
    uint32_t encoded = htons(value);
    data[pos++] = (encoded >> 24) & 0xFF;
    data[pos++] = (encoded >> 16) & 0xFF;
    data[pos++] = (encoded >> 8) & 0xFF;
    data[pos++] = encoded & 0xFF;
    return pos;
}