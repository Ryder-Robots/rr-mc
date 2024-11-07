#include <multiwii.hpp>

using namespace rrobot;
using namespace std;

void MultiWii::calculateChecksum() {
    _mspPackage.checksum = _mspPackage.size ^ static_cast<uint8_t>(_mspPackage.type);
    for (int i = 0; i < _mspPackage.size; i++) {
        uint8_t byte = _mspPackage.payload[i];
        _mspPackage.checksum ^= byte;
    }
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