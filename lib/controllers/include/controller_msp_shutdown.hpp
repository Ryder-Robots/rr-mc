#ifndef CONTROLLER_MSP_SHUTDOWN_HPP
#define CONTROLLER_MSP_SHUTDOWN_HPP

#include <abstract_controller.hpp>
#include <encoder_msp_shutdown.hpp>

namespace rrobot {
class MspShutdownController : public RrController {
   public:
    void* run(void* request) override {
        _shutdown = true;
        return nullptr;
    }

    RrEncoder* encoder() override { return _encoder; }

    bool isShutdown() { return _shutdown; }

   private:
    bool _shutdown = false;
    EncoderMspShutdown* _encoder = new EncoderMspShutdown();
};
}  // namespace rrobot

#endif  // CONTROLLER_MSP_SHUTDOWN_HPP