#include <multiwii.hpp>

/*
 * | element    | position      | type      | byte offset | optional |
 * | ---------- | ------------- | --------  | ----------  | -------- |
 * | command    | 0             | uint8_t   | 1           | no       |
 * | size       | 1, 2          | uint16_t  | 2           | no       |
 * | crc        | 3, 4, 5, 6    | uint32_t  | 4           | no       |
 * | data       | 6             | uint8_t*  | 0 to n      | yes      |
 * | term       | n + 1         | uint8_t*  | 1           | no       |
 */

using namespace rrobot;

/*
 * Main loop called each time loop is executed.
 */
void RrMultiWii::execute(void) {
    _hasError = false;
    while (_serialUsb.available() == 0) {
    }

    // Get command
    RrCommand cmd = _mspFactory.retrieveCommand(_serialUsb.read());
    if (cmd == RrCommand::MSP_UNSUPPORTED) {
        _hasError = true;
        _error = RrError::MSP_CMD_NOT_SUPPORTED;
        return;
    }

    // Get Controller
    RrController* ctl = _mspFactory.retrieveController(cmd);

    // get size
    uint16_t sz = _serialUsb.read() << 8 | _serialUsb.read();
    if (sz > MAX_USB_BF || !(sz == 0 || sz == ctl->encoder()->getSize())) {
        _hasError = true;
        _error = RrError::MSP_SIZE_MISSMATCH;
        return;
    }

    uint8_t* payload = nullptr;
    uint32_t crc = 0;
    if (sz > 0) {
        crc = _serialUsb.read() << 24 | _serialUsb.read() << 16 | _serialUsb.read() << 8 | _serialUsb.read();
        payload = reinterpret_cast<uint8_t*>(malloc(sizeof(uint8_t) * sz));
        for (int n = 0; n < sz; n++) {
            uint8_t c = _serialUsb.read();
            if (c == _termination) {
                _hasError = true;
                _error = RrError::MSP_INVALID_DATA;
                return;
            }

            payload[n] = c;
        }
        // perform CRC check.
        if (crc != _crc32.calculate(payload, sz)) {
            _hasError = true;
            _error = RrError::MSP_INVALID_DATA;
            return;
        }
    }

    uint8_t* result = reinterpret_cast<uint8_t*>(ctl->encoder()->encode(ctl->run(payload)));
    _serialUsb.write(static_cast<uint8_t>(ctl->encoder()->getCommand()));

    sz = ctl->encoder()->getSize();
    _serialUsb.write(highByte(sz));
    _serialUsb.write(lowByte(sz));

    if (ctl->encoder()->getSize() > 0) {
        crc = _crc32.calculate(result, ctl->encoder()->getSize());
        _serialUsb.write(crc >> 24 | 0xFF);
        _serialUsb.write(crc >> 16 | 0xFF);
        _serialUsb.write(crc >> 8 | 0xFF);
        _serialUsb.write(crc);

        for (int n = 0; n < ctl->encoder()->getSize(); n++) {
            _serialUsb.write(result[n]);
        }
    } else {
        _serialUsb.write(0x00);
        _serialUsb.write(0x00);
        _serialUsb.write(0x00);
        _serialUsb.write(0x00);
    }
    _serialUsb.write(_termination);
}

void RrMultiWii::setup() { _mspFactory.setUp(); }

void RrMultiWii::tearDown() { _mspFactory.tearDown(); }