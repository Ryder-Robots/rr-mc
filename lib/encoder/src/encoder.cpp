#include <encoder.hpp>

using namespace rrobot;

uint16_t RrEncoder::decodeUint16(uint8_t* data, int& pos) {
    return (static_cast<uint16_t>(data[pos++]) << 8) | data[pos++];
}

uint32_t RrEncoder::decodeUint32(uint8_t* data, int& pos) {
    uint32_t value = ((uint32_t)data[pos++] << 24 | (uint32_t)data[pos++] << 16 | (uint32_t)data[pos++] << 8 |
                      (uint32_t)data[pos++]);

    return value;
}

int RrEncoder::splitUint16(uint16_t value, uint8_t* data, int pos) {
    data[pos] = (value >> 8) & 0xFF;
    data[pos + 1] = value & 0xFF;
    return pos + 2;
}

int RrEncoder::splitUint32(uint32_t value, uint8_t* data, int pos) {
    data[pos++] = (value >> 24) & 0xFF;
    data[pos++] = (value >> 16) & 0xFF;
    data[pos++] = (value >> 8) & 0xFF;
    data[pos++] = value & 0xFF;
    return pos;
}

int RrEncoder::splitFloat(float value, uint8_t* data, int pos) {
    memcpy(data + pos, &value, sizeof(float));
    return pos + sizeof(float);
}