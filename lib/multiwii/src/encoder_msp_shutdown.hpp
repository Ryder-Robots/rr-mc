#ifndef ENCODER_MSP_SHUTDOWN_HPP
#define ENCODER_MSP_SHUTDOWN_HPP

#include <encoder.hpp>

namespace rrobot
{
    /**
     * Used to allow Pi to give shutdown command to Micro-controller.
     */
    class EncoderMspShutdown : public RrEncoder {
        public:

        RrCommand getCommand() override {
            return RrCommand::MSP_EXIT;
        }

        /**
         * @fn getSize
         * @brief
         * Shutdown is inbound therefore always return 0
         */
        uint16_t getSize() override
        {
            return 0;
        }

        /**
         * @fn encode
         * @brief
         * data is not expected for shutdown.
         */
        uint8_t *encode(void *data) override {return nullptr;}

        /**
         * @fn decode
         * @brief
         * data is not expected for shutdown.
         */
        void *decode(uint8_t *data) override {return nullptr;}

    };
}

#endif // ENCODER_MSP_SHUTDOWN_HPP