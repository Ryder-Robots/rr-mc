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
        uint16_t getSize() override {
            return (sizeof(uint16_t) * 4) + sizeof(uint8_t);
        }

        RrCommand getCommand() override {
            return RrCommand::MSP_STATUS;
        }

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
        uint8_t* encode(void* data) override {
            uint8_t* encoded = static_cast<uint8_t*>(malloc(getSize()));
            MspStatus* obj = static_cast<MspStatus*>(data);
            int pos = splitUint16(obj->get_cycletime(), encoded, 0);
            pos = splitUint16(obj->get_i2c_errors_count(), encoded, pos);
            pos = splitUint16(obj->get_sensor(), encoded, pos);
            pos = splitUint16(obj->get_flag(), encoded, pos);
            encoded[pos] = obj->get_current_set();
            return encoded;
        }


        void* decode(uint8_t *data) override {
            MspStatus *decoded = new MspStatus();
            decoded->set_cycletime(ntohs(decodeUint16(data[0], data[1])));
            decoded->set_i2c_errors_count(ntohs(decodeUint16(data[2], data[3])));
            decoded->set_sensor(ntohs(decodeUint16(data[4], data[5])));
            decoded->set_flag(ntohs(decodeUint16(data[6], data[7])));
            decoded->set_current_set(data[8]);

            return static_cast<void*>(decoded);
        }

        private:
            int splitUint16(uint16_t value, uint8_t* data, int pos) {
                uint16_t encoded = htons(value);
                data[pos] = (value >> 8) & 0xFF;
                data[pos + 1] = value & 0xFF;
                return pos + 2;
            }

            uint16_t decodeUint16(uint8_t highByte, uint8_t lowByte) {
                return (static_cast<uint16_t>(highByte) << 8) | lowByte;
            }
    };
}

#endif