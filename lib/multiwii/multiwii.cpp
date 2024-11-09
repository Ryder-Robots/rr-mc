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

uint8_t* MultiWii::serialize(const MspCommands type, const uint8_t size, uint8_t* payload) {
    _type = type;
    setDirection(Direction_t::outbound);
    setPayload(payload, size);
    _checksum = calculateChecksum();

    uint8_t* package = (uint8_t*)malloc((pkgOffset + size) * sizeof(uint8_t));

    int i = 0;
    for (i = 0; i < 2; i++) {
        package[i] = static_cast<uint8_t>(_hdr[i]);
    }
    package[2] = static_cast<uint8_t>(_direction);
    package[3] = size;
    package[4] = static_cast<uint8_t>(_type);
    i = 5;
    for (int y = 0; y < _size; y++) {
        package[i++] = _payload[y];
    }
    package[i] = _checksum;

    return package;
}

bool MultiWii::verifyHeader(uint8_t* packet) {
    bool result = true;

    if (packet[0] != _hdr[0]) {
        result = false;
    } else if (packet[1] != _hdr[1]) {
        result = false;
    }

    return result;
}

template <typename T>
T assignType(const T validValues[], const int s, const uint8_t cbkValue, const T elsV) {
    for (int i = 0; i < s; i++) {
        T v = validValues[i];
        if (cbkValue == static_cast<uint8_t>(v)) {
            return v;
            break;
        }
    }

    return elsV;
}

int MultiWii::deserialize(uint8_t* packet, const uint8_t size) {
    if (!verifyHeader(packet)) {
        return RrExceptions::RR_MSP_HEADER;
    }

    // there should be at least one value in the payload.
    if (size < (pkgOffset + 1)) {
        return RrExceptions::RR_MSP_INVALID_LEN;
    }
    uint8_t direction = packet[2];
    setDirection(assignType(VALID_DIRECTIONS, VALID_DIRECTIONS_CNT, direction, Direction_t::invalid));
    static constexpr int validCmdCnt = sizeof(VALID_CMDS) / sizeof(VALID_CMDS[0]);
    _size = packet[3];
    uint8_t cmd = packet[4];
    setType(assignType(VALID_CMDS, validCmdCnt, cmd, MspCommands::MSP_INVALID));

    _payload = (uint8_t*)malloc(_size * sizeof(uint8_t));
    for (int i = 0; i < _size; i++) {
        // check still in bounds.
        if ((i + pkgOffset + 1) > size) {
            return RrExceptions::RR_MSP_INVALID_LEN;
        }

        _payload[i] = packet[5 + i];
    }

    if (getDirection() == Direction_t::invalid || getType() == MspCommands::MSP_INVALID) {
        return RrExceptions::RR_INVALID_FIELD;
    }

    // perform CRC check, always do this at the end, an invalid checksum may not be the end of the
    // world depending on what the command is, how critical.  If it is likely to crash something
    // then it's bad. For instance its a request to give more voltage to an engine, then it's critical.
    //
    // If it is a request for how hot the temprature is then it's ok to return something.
    //
    // Note that the MSP_STATUS response should always regard an invalid checksum as an error,
    // and report it back.
    uint8_t crc = packet[5 + _size];
    if (calculateChecksum() != crc) {
        return RrExceptions::RR_INVALID_CHECKSUM;
    }

    return 0;
}

/**
 * Checksum is used to validate inbound packages.
 */
uint8_t MultiWii::calculateChecksum() {
    uint8_t checksum = 0;
    checksum ^= _size;
    checksum ^= static_cast<uint8_t>(_type);
    for (int i = 0; i < _size; i++) {
        checksum ^= _payload[i];
    }
    return checksum;
}

void MultiWii::setPayload(uint8_t* payload, uint8_t size) {
    _payload = (uint8_t*)malloc(size * sizeof(uint8_t));
    memcpy(_payload, payload, size * sizeof(uint8_t));
    _size = size;
}

void MultiWii::setDirection(Direction_t direction) { _direction = direction; }

Direction_t MultiWii::getDirection() { return _direction; }

void MultiWii::setType(MspCommands command) { _type = command; }

MspCommands MultiWii::getType() { return _type; }

uint8_t* MultiWii::getPayload() { return _payload; }
