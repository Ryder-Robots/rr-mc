#include <abstract_controller.hpp>

using namespace rrobot;

uint8_t* RrController::execute(uint8_t* command) {
    RrMultiWii multiWii(encoder(), _crc);
    uint16_t sz = 0;
    uint8_t* payload = multiWii.decodePayload(command);

    void* decoded = encoder()->decode(payload);
    void* result = run(decoded);
    return multiWii.encode(result);
}