#ifndef MULTIWII_HPP
#define MULTIWII_HPP

// The following libraries should be defined in a macro at build time.
#include <Arduino.h>
#include <stdint.h>
#include <encoder.hpp>
#include <crc.hpp>

namespace rrobot {

    /**
     * @class RrMultiWii
     * @brief
     * MultiWii data structure.
     */
    template <class T>
    class RrMultiWii {
        public:
            RrMultiWii(RrEnecoder<T>* encoder, Crc32 crc32):
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
            uint16_t    getSize() {return _encoder->getSize();}
            
            /**
             * @fn encode
             * @brief
             * given data of type T encode it to packet that can be transmitted through serial port.
             * 
             * By default this also sets the direction to outbound.
             */
            uint8_t*    encode(T data) {
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
                    uint16_t sz = htons(_encoder->getSize());
                    packet[i++] =  (sz >> 8) & 0xFF;
                    packet[i++] = sz & 0xFF;
                    packet[i++] = static_cast<uint8_t>(_encoder->getCommand()) & 0xFF;

                    const uint8_t* encoded =  _encoder->encode(data);
                    for (int c = 0; c < sizeof(encoded); c++) {
                        packet[i++] = encoded[c];
                    }

                    // CRC check goes here.
                    uint32_t crc = htonl(_crc32.calculate(encoded, _encoder->getSize()));
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


            /**
             * @fn decode
             * @brief
             * Given network packet decode it, and set internal variables.
             */
            T decode(uint8_t* data) {
                // need logic here to decode.
            }

            /**
             * @fn reset
             * @brief
             * resets command.
             */
            void reset() {_direction = RrDirection::MWC_ERROR;}


        private:
            const char  _preamble[2] = {'$', 'M'};
            RrEnecoder<T>*  _encoder;
            RrDirection _direction = RrDirection::MWC_ERROR;
            const char _termination = 0x1E;
            Crc32 _crc32;
    };
}

#endif