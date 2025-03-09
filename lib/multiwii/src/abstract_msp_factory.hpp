#ifndef ABSTRACT_MSP_FACTORY_HPP
#define ABSTRACT_MSP_FACTORY_HPP

#include <abstract_controller.hpp>

namespace rrobot {

    /**
     * @class AbstractMspFactory
     * @brief
     * Retrieves controllers given either input data or factory class.
     */
    class AbstractMspFactory {
        public:

        /**
         * @fn retrieveEncoder()
         * @brief
         * retrieve controller given inbound data.
         */
        virtual RrController* retrieveEncoder(uint8_t *data) = 0;

        /**
         * @fn retrieveEncoder()
         * @brief
         * intended for inter controller communication, using command, return controller.
         */
        virtual RrController*  retrieveEncoder(RrCommand command) = 0;

        /**
         * @fn setUp
         * @brief
         * Called at setup of the main loop, used to perform any initlization that controllers may need.
         */
        virtual void setUp() {}

        /**
         * @fn tearDown
         * @brief
         * Called as part of shutdown, used to perform any teardown functionality.
         */
        virtual void tearDown() {}
    };
}

#endif