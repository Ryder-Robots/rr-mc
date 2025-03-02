#include <multiwii.hpp>


using namespace rrobot;


uint8_t*  RrMultiWii::encode(void* data) {
    uint8_t* out = _encoder->encode(data);
    uint8_t* packet = reinterpret_cast<uint8_t *>(malloc(
        sizeof(_preamble) + sizeof(_direction) + _encoder->getSize() +
        sizeof(uint32_t) + sizeof(_termination)
    ));

    int i = 0;
    for (char c : _preamble) {
        packet[i++] = c;
    }

    if (_encoder->getSize() != 0) {
        uint16_t sz = _encoder->getSize();
        packet[i++] =  (sz >> 8) & 0xFF;
        packet[i++] = sz & 0xFF;
        packet[i++] = static_cast<uint8_t>(_encoder->getCommand()) & 0xFF;

        const uint8_t* encoded =  _encoder->encode(data);
        for (int c = 0; c < _encoder->getSize(); c++) {
            packet[i++] = encoded[c] & 0xFF;
        }

        // CRC check goes here.
        uint32_t crc = _crc32.calculate(encoded, _encoder->getSize());

        packet[i++] = (crc >> 24) & 0xFF;
        packet[i++] = (crc >> 16) & 0xFF;
        packet[i++] = (crc >> 8) & 0xFF;
        packet[i++] = crc & 0xFF;
    } else {
        // CRC and size are both set to 0
        packet[i++] = 0 & 0xFF;
        packet[i++] = 0 & 0xFF;
        packet[i++] = static_cast<uint8_t>(_encoder->getCommand()) & 0xFF;
        packet[i++] = 0 & 0xFF;    
        packet[i++] = 0 & 0xFF;
        packet[i++] = 0 & 0xFF;
        packet[i++] = 0 & 0xFF;    
    }

    packet[i] = _termination & 0xFF;
    return packet;
}


uint8_t* RrMultiWii::decodePayload(uint8_t* data) {
    // need logic here to decode.

    uint16_t sz = (uint16_t)data[3] | ((uint16_t)data[4] << 8);
    uint8_t* payload =  nullptr;

    if (sz != 0) {
        payload = reinterpret_cast<uint8_t *>(malloc(sizeof(uint8_t) * sz));
        for (int i = 0; i < sz; i++) {

            if (payload[i] == _termination) {
                // throw exception.
            }

            payload[i] = data[5 + i];
        }
    }

    return payload;
}