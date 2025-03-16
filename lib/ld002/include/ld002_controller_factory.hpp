#ifndef LD001_CONTROLLER_FACTORY_HPP
#define LD001_CONTROLLER_FACTORY_HPP

#include <abstract_msp_factory.hpp>
#include <controller_msp_sensor.hpp>
#include <controller_msp_shutdown.hpp>
#include <controller_msp_status.hpp>

namespace rrobot {
class Ld001ControllerFactory : public AbstractMspFactory {
   public:
    RrController* retrieveController(RrCommand command) override;
    RrCommand retrieveCommand(uint8_t cmd) override;

   private:
    MspStatusController* _statusController = new MspStatusController();
    MspSensorController* _sensorController = new MspSensorController();
    MspShutdownController* _shutdownController = new MspShutdownController();
};
}  // namespace rrobot

#endif