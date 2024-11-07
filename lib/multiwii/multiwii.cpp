#include <multiwii.hpp>

using namespace rrobot;
using namespace std;


/**
 * When serializing message it should always be considered outbound.
 */
uint8_t* MultiWii::serialize(MspCommands type, uint8_t size, uint8_t *payload) {
    _mspPackage.type = type;
    setDirection(Direction_t::outbound);
    setPayload(payload, size);
    _mspPackage.checksum = calculateChecksum();

    return reinterpret_cast<uint8_t*>(&_mspPackage);
}

uint8_t MultiWii::calculateChecksum() {
    uint8_t checksum = _mspPackage.size ^ static_cast<uint8_t>(_mspPackage.type);
    for (int i = 0; i < _mspPackage.size; i++) {
        uint8_t byte = _mspPackage.payload[i];
        checksum ^= byte;
    }
    return checksum;
}

void MultiWii::setPayload(uint8_t* payload, uint8_t size) {
    memcpy(_mspPackage.payload, payload, size);
    _mspPackage.size = size;
}

void MultiWii::setDirection(Direction_t direction) {
    _mspPackage.direction = direction;
}

Direction_t MultiWii::getDirection() {
    return _mspPackage.direction;
}

void MultiWii::setType(MspCommands command) {
    _mspPackage.type = command;
}

MspCommands MultiWii::getType() {
    return _mspPackage.type;
}

uint8_t* MultiWii::getPayload() {
    return _mspPackage.payload;
}