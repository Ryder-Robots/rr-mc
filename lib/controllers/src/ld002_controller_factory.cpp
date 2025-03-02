#include <ld002_controller_factory.hpp>

using namespace rrobot;

RrController* Ld001ControllerFactory::retrieveEncoder(uint8_t *data) {
    RrCommand cmd = static_cast<RrCommand>(data[5]);
    return retrieveEncoder(cmd);
}

RrController*  Ld001ControllerFactory::retrieveEncoder(RrCommand command) {
    switch(command) {
        case RrCommand::MSP_STATUS:
            return _statusController;
    }

    return nullptr;
}