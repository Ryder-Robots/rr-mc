#ifndef ENCODER_MSP_STATUS_HPP
#define ENCODER_MSP_STATUS_HPP

#include <Arduino.h>

#include <encoder.hpp>
#include <msp_status.hpp>

namespace rrobot {
/**
 * @class MspIdentEncoder
 * @brief
 * implemnentation of RrEncoder for MspIdent command
 */
class EncoderMspStatus : public RrEncoder {
   public:
    uint16_t getSize() override { return (sizeof(uint16_t) * 3) + sizeof(uint32_t) + sizeof(uint8_t); }

    RrCommand getCommand() override { return RrCommand::MSP_STATUS; }

    /**
     * @fn encode
     * @brief
     * encodes MspIdent object to something that can be sent through serial port.
     *
     *  variable order is:
     *   uint16_t _cycletime;
     *   uint16_t _i2c_errors_count;
     *   uint16_t _sensor;
     *   uint32_t _flag;
     *   uint8_t  _current_set;
     */
    uint8_t *encode(void *data) override;

    void *decode(uint8_t *data) override;
};
}  // namespace rrobot

#endif