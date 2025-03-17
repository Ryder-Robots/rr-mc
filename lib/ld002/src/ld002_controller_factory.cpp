#include <ld002_controller_factory.hpp>

using namespace rrobot;

RrController* Ld001ControllerFactory::retrieveController(RrCommand command) {
    switch (command) {
        case RrCommand::MSP_STATUS:
            return _statusController;
            break;
        case RrCommand::MSP_SENSOR:
            return _sensorController;
            break;
        case RrCommand::MSP_EXIT:
            return _shutdownController;
            break;
    }

    // if encoder not found then status is a pretty safe bet.
    return _statusController;
}

RrCommand Ld001ControllerFactory::retrieveCommand(uint8_t cmd) {
    RrCommand result = RrCommand::MSP_UNSUPPORTED;
    switch (static_cast<RrCommand>(cmd)) {
        case RrCommand::MSP_STATUS:
            result = RrCommand::MSP_STATUS;
            break;
        case RrCommand::MSP_SENSOR:
            result = RrCommand::MSP_SENSOR;
            break;
        case RrCommand::MSP_EXIT:
            result = RrCommand::MSP_EXIT;
            break;

        default:
            RrCommand::MSP_UNSUPPORTED;
    }
    return result;
}