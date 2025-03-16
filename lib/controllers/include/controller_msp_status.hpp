#ifndef CONTROLLER_MSP_STATUS_HPP
#define CONTROLLER_MSP_STATUS_HPP

#include <abstract_controller.hpp>
#include <encoder_msp_status.hpp>

namespace rrobot {
class MspStatusController : public RrController {
   public:
    void* run(void* request) override;

    RrEncoder* encoder() override;

    void set_cycletime(uint16_t cycletime) { _cycletime = cycletime; }

    void set_i2c_errors_count(uint16_t i2c_errors_count) { _i2c_errors_count = i2c_errors_count; }

    void set_flag(RRP_STATUS flag) { _flag = flag; }

    void set_current_set(uint8_t current_set) { _current_set = current_set; }

   private:
    uint16_t _cycletime = 0;
    uint16_t _i2c_errors_count = 0;
    RRP_STATUS _flag = RRP_STATUS::INITILIZING;
    uint8_t _current_set = 0;

    // hard coded sensors
    const uint16_t _sensors =
        static_cast<uint16_t>(RrMspSensorFlags::BARO) | static_cast<uint16_t>(RrMspSensorFlags::GPS) |
        static_cast<uint16_t>(RrMspSensorFlags::MAG) | static_cast<uint16_t>(RrMspSensorFlags::SONAR);

    EncoderMspStatus* _encoder = new EncoderMspStatus();
};
}  // namespace rrobot

#endif  // CONTROLLER_MSP_STATUS_HPP