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

        // TODO: Need to send back error here for MSP_UNSUPPORTED
    }

    // if encoder not found then status is a pretty safe bet.
    return _statusController;
}

/*
 * Not sure why a case statement won't work here, but for some reason it doesn't. Nested if then else does though.
 */
RrCommand Ld001ControllerFactory::retrieveCommand(uint8_t cmd) {
    RrCommand result = RrCommand::MSP_UNSUPPORTED, test = static_cast<RrCommand>(cmd);
    if (test == RrCommand::MSP_STATUS)
        result = RrCommand::MSP_STATUS;
    else if (test == RrCommand::MSP_SENSOR)
        result = RrCommand::MSP_SENSOR;
    else if(test == RrCommand::MSP_EXIT)
        result = RrCommand::MSP_EXIT;
    return result;
}