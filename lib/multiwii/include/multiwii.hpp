#ifndef MULTIWII_HPP
#define MULTIWII_HPP

// The following libraries should be defined in a macro at build time.
#include <Arduino.h>
#include <stdint.h>

#include <abstract_msp_factory.hpp>
#include <crc.hpp>
#include <encoder.hpp>
#include <serial_usb.hpp>
#include <rrerror.hpp>

namespace rrobot {

/**
 * @class RrMultiWii
 * @brief
 * MultiWii data structure.
 */
class RrMultiWii {
   public:
    RrMultiWii(RrEncoder* encoder, Crc32 crc32, AbstractMspFactory* mspFactory)
        : _encoder(encoder), _crc32(crc32), _mspFactory(mspFactory) {}

    /**
     * @fn getSize
     * @brief
     * return size of data in bytes
     */
    uint16_t getSize() { return _encoder->getSize(); }

    void setup();
    void tearDown();
    void execute();

   private:
    RrEncoder* _encoder;
    const char _termination = 0x1E;
    Crc32 _crc32;
    AbstractMspFactory* _mspFactory;
    SerialUsb _serialUsb = SerialUsb();
    bool _hasError = false;
    RrError _error = RrError::MSP_OK;

    const uint16_t MAX_USB_BF = 512;
};
}  // namespace rrobot

#endif