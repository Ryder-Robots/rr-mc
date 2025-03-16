#ifndef CONTROLLER_MSP_SENSOR_HPP
#define CONTROLLER_MSP_SENSOR_HPP

#include <abstract_controller.hpp> 
#include <ble.hpp>
#include <msp_sensor.hpp>
#include <encoder_msp_sensor.hpp>

namespace rrobot {
    class MspSensorController : public RrController {
        public:
        void* run(void* command) override;

        RrEncoder* encoder() override;

        private:
        EncoderMspSensor* _encoder = new EncoderMspSensor();
        Ble ble = Ble();
    };
}

#endif // CONTROLLER_MSP_SENSOR_HPP