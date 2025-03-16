#ifndef ABSTRACT_CONTROLLER_HPP
#define ABSTRACT_CONTROLLER_HPP

#include <stdint.h>

#include <encoder.hpp>

namespace rrobot {
/**
 * @class RrManager
 *
 * @brief
 * input is recieved add send to the execute method,  this is processed and returned
 * and returns a result from the execution.
 */
class RrController {
   public:
    /**
     * @fn execute
     * @brief
     * internal execution of the command, for controller to controller communication.
     */
    virtual void* run(void* request) = 0;

    /**
     * @fn encoder()
     * @brief
     * returns encoder for controller.
     */
    virtual RrEncoder* encoder() = 0;
};
}  // namespace rrobot

#endif  // ABSTRACT_CONTROLLER_HPP