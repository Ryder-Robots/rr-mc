#ifndef ENCODER_MSP_SENSOR_HPP
#define ENCODER_MSP_SENSOR_HPP

#include <Arduino.h>
#include <encoder.hpp>
#include <msp_sensor.hpp>
#include <ble.hpp>

namespace rrobot {
    class EncoderMspSensor : public RrEncoder {
    public:
        uint16_t getSize() override
        {
            return (sizeof(int32_t)* 3 + (sizeof(float) * 9));
        }

        RrCommand getCommand() override
        {
            return RrCommand::MSP_SENSOR;
        }

        /**
         * @fn encode
         * @brief
         * encodes MspSensor object to something that can be sent through serial port.
         *
         * _acc_avail int32
         * _acc_x float
         * _acc_y float
         * _acc_z float
         * _gyro_avail int32
         * _gyro_x float
         * _gyro_y float
         * _gyro_z float
         * _mag_avail int32
         * _mag__x float
         * _mag__y float
         * _mag__z float
         * 
         * 
         */
        uint8_t *encode(void *data) override;

        void *decode(uint8_t *data) override;
    };
}

#endif // ENCODER_MSP_SENSOR_HPP