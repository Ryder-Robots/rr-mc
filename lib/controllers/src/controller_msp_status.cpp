#include <controller_msp_status.hpp>


using namespace rrobot;

// Return multi wii object using encoder, and refering the bottom encoder.
// this routine can be moved to the abstract controller.
uint8_t* MspStatusController::execute(uint8_t *) {
    return nullptr;
}


void* MspStatusController::execute(void* command) {

    MspStatus* status = new MspStatus();

    status->set_cycletime(_cycletime);
    status->set_i2c_errors_count(_i2c_errors_count);
    status->set_sensor(_sensors);
    status->set_flag(_flag);
    status->set_current_set(_current_set);

    return status;
}