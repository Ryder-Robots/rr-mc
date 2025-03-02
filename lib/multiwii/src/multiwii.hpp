#ifndef MULTIWII_HPP
#define MULTIWII_HPP

// The following libraries should be defined in a macro at build time.
#include <Arduino.h>
#include <stdint.h>
#include <crc.hpp>
#include <encoder.hpp>

namespace rrobot {

    /**
     * @class RrMultiWii
     * @brief
     * MultiWii data structure.
     */
    class RrMultiWii {
        public:
            RrMultiWii(RrEncoder* encoder, Crc32 crc32):
                _encoder(encoder), _crc32(crc32) {}

            /**
             * @fn getDirection
             * @brief
             * returns direction of data.
             */
            RrDirection getDirection() {return _direction;}

            /**
             * @fn getSize
             * @brief
             * return size of data in bytes
             */
            uint16_t getSize() {return _encoder->getSize();}
            
            /**
             * @fn encode
             * @brief
             * given data of type T encode it to packet that can be transmitted through serial port.
             * 
             * By default this also sets the direction to outbound.
             */
            uint8_t* encode(void* data);

            /**
             * @fn reset
             * @brief
             * resets command.
             */
            void reset() {_direction = RrDirection::MWC_ERROR;}

            void* decode(uint8_t *data)
            {
                uint8_t* payload = decodePayload(data);
                return _encoder->decode(payload);
            }
            uint8_t* decodePayload(uint8_t* data);
        private:
            const char  _preamble[2] = {'$', 'M'};
            RrEncoder*  _encoder;
            RrDirection _direction = RrDirection::MWC_ERROR;
            const char _termination = 0x1E;
            Crc32 _crc32;
    };
}

#endif