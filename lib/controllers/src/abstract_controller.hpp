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
        // TODO, instead assuming the data is already read,  read it here, this way default can be set.
        public:
        /**
         * @fn execute
         * @brief
         * given data execute command.
         */
        uint8_t* execute(uint8_t *data);


        //TODO: This should change to command, and optional data if any. Perhaps use run() instead of execute sothere
        // is a distinction.
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

        private:
        Crc32 _crc;
    };
}

#endif // ABSTRACT_CONTROLLER_HPP