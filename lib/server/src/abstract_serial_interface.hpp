#ifndef ABSTRACT_SERIAL_INTERFACE_HPP
#define ABSTRACT_SERIAL_INTERFACE_HPP

#include <Arduino.h>

namespace rrobot {
    /**
     * @class RrSerial
     * @brief
     * Connects to USB interface
     */
    class AbstractUsbInterface {

        /**
         * given board rate start communication, note that for UART this MUST be overridden at pin
         * position will need to be defined. Override is required for GPS communication with UART chip.
         */
        virtual void begin(unsigned long) = 0;

        virtual size_t write(const uint8_t*, size_t) = 0;

        /**
         * @fn flush
         * @brief
         * flush buffer.
         */
        virtual void flush(void) = 0;

        /**
         * @fn available
         * @brief
         * returns > 0 when data is available.
         */
        virtual int available(void) = 0;

        /**
         * @fn read
         * @brief
         * read single byte at a time.
         */
        virtual uint8_t* read(void) = 0;
    };
}

#endif // ABSTRACT_SERIAL_INTERFACE_HPP