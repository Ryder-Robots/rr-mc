#ifndef RRPHEADER_HPP
#define RRPHEADER_HPP

#include <stdint.h>
#include <rrcommands.hpp>
#include <Arduino.h>

namespace rrobot {
/**
 * @class encoder
 * @brief
 * abstract interface that encodes and decodes mullti-wii commmand.
 */
class RrEncoder {
   public:
    /**
     * @fn getSize()
     * @brief
     * returns size of object in byres.
     */
    virtual uint16_t getSize() = 0;

    /**
     * @fn getCommand
     * @brief
     * command that is getting encoded/decoded
     */
    virtual RrCommand getCommand() = 0;

    /**
     * @fn encode
     * @brief
     * when given data of type T encode it to uint8_t that is using hton format
     * @param data to be encoded.
     */
    virtual uint8_t* encode(void* data) = 0;

    /**
     * @fn decode
     * @brief
     * when given encoded data, desialize and return variable of type T.
     */
    virtual void* decode(uint8_t* data) = 0;

    int splitUint16(uint16_t value, uint8_t* data, int pos);
    int splitUint32(uint32_t value, uint8_t* data, int pos);
    int splitFloat(float value, uint8_t* data, int pos);

    uint16_t decodeUint16(uint8_t* data, int& pos);
    uint32_t decodeUint32(uint8_t* data, int& pos);
};
}  // namespace rrobot

#endif