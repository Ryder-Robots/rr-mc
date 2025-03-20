#ifndef SERIAL_USB_HPP
#define SERIAL_USB_HPP

#include <abstract_serial_interface.hpp>

namespace rrobot {

/**
 * interface to USB,  MultiWii communication from Pi to Arduino is done using this interface.
 */
class SerialUsb : public AbstractUsbInterface {
   public:
    /**
     * @fn begin
     * @brief
     * initlize communication, this should be done during setup() phase of main program.
     */
#ifdef NATIVE
    void begin(unsigned long baud) override {}
#else
    void begin(unsigned long baud) override {
        Serial.begin(baud);
        while (!Serial);
    }
#endif

    /**
     * @fn write
     * @brief
     * write bytes to USB.
     */
    size_t write(const uint8_t) override;

    /**
     * @fn flush
     * @brief
     * flush USB buffer
     */
    void flush(void) override;

    /**
     * @fn available
     * @brief
     * if > 0 returns bytes available on buffer, note that anything greater than 1 should be read,
     * and the assumption that it is all the data available is wrong.
     */
    int available(void) override;

    /**
     * @fn read
     * @brief
     * read data from the buffer and return the all data up to and including termination string.
     */
    uint8_t read(void) override;

   private:

    uint8_t _tm = 0x1E;
    size_t _mxbuf = sizeof(uint8_t) * 512;
};
}  // namespace rrobot

#endif  // SERIAL_USB_HPP