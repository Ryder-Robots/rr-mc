#ifndef ENCODER_MSP_IDENT_HPP
#define ENCODER_MSP_IDENT_HPP

#include <Arduino.h>

#include <encoder.hpp>
#include <msp_ident.hpp>

namespace rrobot {
/**
 * @class MspIdentEncoder
 * @brief
 * implemnentation of RrEnecoder for MspIdent command
 */
class MspIdentEncoder : public RrEnecoder<MspIdent> {
   public:
    uint16_t getSize() override { return 0; }

    RrCommand getCommand() override { return RrCommand::MSP_IDENT; }

    /**
     * @fn encode
     * @brief
     * encodes MspIdent object to something that can be sent through serial port.
     */
    uint8_t* encode(MspIdent data) override {
        uint8_t* encoded = static_cast<uint8_t*>(malloc(getSize()));
        return encoded;
    }

    MspIdent decode(uint8_t* data) override {
        MspIdent decoded;

        return decoded;
    }
};
}  // namespace rrobot

#endif