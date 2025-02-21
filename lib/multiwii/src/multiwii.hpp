#ifndef MULTIWII_HPP
#define MULTIWII_HPP

// The following libraries should be defined in a macro at build time.
#include <Arduino.h>
#include <Ethernet.h>

#include <stdint.h>

namespace rrobot {

    /**
     * @class RrDirection
     * @brief
     * Direction on request
     */
    enum class RrDirection : char {
        MWC_TO    = '<',
        MWC_FROM  = '>',
        MWC_ERROR = '!'
    };

    enum class RrCommand : uint8_t {
        MSP_STATUS = 101,
        MSP_GYRO   = 216,
    };

    /**
     * @class RrMultiWii
     * @brief
     * MultiWii data structure.
     */
    class RrMultiWii {
        public:
            RrMultiWii(RrDirection direction, uint16_t size, RrCommand command, uint8_t* data):
                _direction(direction),
                _size(htons(size)),
                _command(command),

                // ensure that anything that has a word size larger than uint8_t is encoded using htons
                _data(data) {}

            uint8_t* encode();
            void     decode(uint8_t* data);

            RrDirection getDirection() {return _direction;}
            uint16_t    getSize() {return ntohs(_size);}
            RrCommand   getCommand() {return _command;}
            uint8_t*    getData() {return _data;}

        private:
            const char  _preamble[2] = {'$', 'M'};
            RrDirection _direction = MWC_FROM;

            // uint16_t number but must be stored as MSB this is done using htons
            uint16_t     _size     = 0;
            RrCommand    _command  = MSP_STATUS;
            uint8_t*     _data      = nullptr;

            //checksum
            uint16_t    _crc       = 0;

            // termination character is used because it is a good idea.
            const char _termination = 0x1E;
    };
}

#endif