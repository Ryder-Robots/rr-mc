#include <multiwii.hpp>

using namespace rrobot;
using namespace std;

/**
 * Using traditional methods for malloc, this is because Arduino malloc is not the
 * same as other implementations, and while it should work,  lets not risk it.
 */

/**
 * When serializing message it should always be considered outbound.
 */
uint8_t* MultiWii::serialize(MspCommands type, uint8_t size, uint8_t *payload) {
    _type = type;
    setDirection(Direction_t::outbound);
    setPayload(payload, size);
    _checksum = calculateChecksum();

    uint8_t* package = (uint8_t*) malloc((pkgOffset + size) * sizeof(uint8_t));

    int i = 0;
    for (i = 0; i < 2; i++) {
          package[i] = static_cast<uint8_t>(_hdr[i]);
    }
    package[2] = static_cast<uint8_t>(_direction);
    package[3] = static_cast<uint8_t>(_type);
    i = 4;
    for (int y = 0; y < _size; y++) {
        package[i++] = _payload[y];
    }
    package[i] = _checksum;

   return package;
}

/**
 * Checksum is used to validate inbound packages.
 */
uint8_t MultiWii::calculateChecksum() {
    uint8_t checksum = 0;
    checksum ^= _size;
    checksum ^= static_cast<uint8_t>(_type);
    for (int i = 0; i < _size; i++) {
        checksum ^=  _payload[i];
    }  
    return checksum;
}

void MultiWii::setPayload(uint8_t* payload, uint8_t size) {

    _payload = (uint8_t*) malloc(size * sizeof(uint8_t));
    memcpy(_payload, payload, size * sizeof(uint8_t));
    _size = size;
}

void MultiWii::setDirection(Direction_t direction) {
    _direction = direction;
}

Direction_t MultiWii::getDirection() {
    return _direction;
}

void MultiWii::setType(MspCommands command) {
    _type = command;
}

MspCommands MultiWii::getType() {
    return _type;
}

uint8_t* MultiWii::getPayload() {
    return _payload;
}
