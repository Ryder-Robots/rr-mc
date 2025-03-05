#ifndef LD001_CONTROLLER_FACTORY_HPP
#define LD001_CONTROLLER_FACTORY_HPP

#include <abstract_msp_factory.hpp>
#include <controller_msp_status.hpp>
#include <controller_msp_sensor.hpp>

namespace rrobot {
    class Ld001ControllerFactory: public AbstractMspFactory {
        public:
        RrController* retrieveEncoder(uint8_t *data) override;

        RrController*  retrieveEncoder(RrCommand command) override;

        private:
        MspStatusController* _statusController = new MspStatusController();
        MspSensorController* _sensorController = new MspSensorController();
    };
}

#endif