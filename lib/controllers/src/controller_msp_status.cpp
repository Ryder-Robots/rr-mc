#include <controller_msp_status.hpp>

using namespace rrobot;

void* MspStatusController::run(void* request) {
    MspStatus* status = new MspStatus();

    status->set_cycletime(_cycletime);
    status->set_i2c_errors_count(_i2c_errors_count);
    status->set_sensor(_sensors);
    status->set_flag(_flag);
    status->set_current_set(_current_set);

    return status;
}

RrEncoder* MspStatusController::encoder() { return _encoder; }