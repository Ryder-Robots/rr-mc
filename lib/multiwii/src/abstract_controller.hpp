#ifndef ABSTRACT_CONTROLLER_HPP
#define ABSTRACT_CONTROLLER_HPP

#include <stdint.h>
#include <multiwii.hpp>

namespace rrobot {
    /**
     * @class RrManager
     * 
     * @brief
     * input is recieved add send to the execute method,  this is processed and returned
     * and returns a result from the execution. 
     */
    class RrController {

        /**
         * @fn execute
         * @brief
         * given data execute command.
         */
        virtual uint8_t* execute(uint8_t *data) = 0;


        /**
         * @fn execute
         * @brief
         * internal execution of the command, for controller to controller communication.
         */
        virtual void* execute(void* command) = 0; 
    };
}

#endif // ABSTRACT_CONTROLLER_HPP