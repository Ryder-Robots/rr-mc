#ifndef RRPHEADER_HPP
#define RRPHEADER_HPP

#include <rrpheader.hpp>

/**
 * 
 */

 namespace rrobot {
    /**
     * @class encoder
     * @brief
     * abstract interface that encodes and decodes mullti-wii commmand.
     */
    template <class T>
    class RrEnecoder {
        public: 
            /**
             * @fn getSize()
             * @brief
             * returns size of object in byres.
             */
            virtual uint16_t getSize() = 0;

            /**
             * @fn getCommand
             * @brief
             * command that is getting encoded/decoded
             */
            virtual RrCommand getCommand() = 0;

            /**
             * @fn encode
             * @brief
             * when given data of type T encode it to uint8_t that is using hton format
             * @param data to be encoded.
             */
            virtual uint8_t* encode(T data) = 0;

            /**
             * @fn decode
             * @brief
             * when given encoded data, desialize and return variable of type T.
             */
            virtual T decode(uint8_t* data);
    };
 }

 #endif