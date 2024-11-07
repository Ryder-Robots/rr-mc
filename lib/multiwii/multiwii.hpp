#ifndef MULTIWII_HPP
#define MULTIWII_HPP

/**
 * MSP message have the following structure:
 *    Header (3 bytes) (ASCII)
 *    Size (1 byte)
 *    Type (1 byte)
 *    Data payload (variable length)
 *    Checksum (1 byte)
 */

#include <stdint.h>
#include <string.h>
#include "commands.hpp"

using namespace std;

namespace rrobot {

    enum class Direction_t : char {
        inbound  = '<',
        outbound = '>',
    };

    // standard MSP package.
    struct MspPackage_t {
        char*     hdr;
        Direction_t  direction;
        uint8_t      size;
        MspCommands  type;
        uint8_t*     payload;
        uint8_t      checksum;

        MspPackage_t() : hdr(preamble) {}

        static constexpr char* preamble = "$M";
    };

    // // 
    // struct MspStatusPayload {
    //     uint16_t cycleTime;
    //     uint16_t i2cErrors;
    //     uint16_t sensors;
    //     uint32_t flags;
    //     uint8_t  currentSet;
    // };

    /**
     * @class MultiWii
     * @brief base class for MSP commands, this class should not be invoked directly.  It is used
     * as part of MSP commands. For serialization and desialization of ingress, and egress messages.
     */
    class MultiWii {
        public:

            /**
             * @fn serialize
             * @brief serializes outbound messages, and sets all getters and setters.
             * @param command MSP command to send.
             * @param size size in bytes of payload.
             * @param payload payload to send.
             */
            uint8_t* serialize(MspCommands, uint8_t size, uint8_t *payload);
            
            /**
             * @fn deserialize
             * @brief called by factory to perform initial deserialization of inbound message. Evoked by
             * factory which perform the conversion to inbound message that can be processed.
             */
            uint8_t* deserialize(uint8*);

            /**
             * @fn setDirection
             * @brief sets either inbound or outbound direction of message.
             * @brief direction
             */
            void setDirection(Direction_t);
            Direction_t getDirection();

            /**
             * @fn setType
             * @brief sets command.
             */
            void setType(MspCommands);
            MspCommands getType();

            /**
             * @fn setPayload
             * @brief set the payload
             * @param payload the payload to attach
             * @param size size of the payload.
             */
            void setPayload(uint8_t*, uint8_t);
            uint8_t* getPayload();

        private:
             struct MspPackage_t _mspPackage;

                 /**
                 * @fn calculateChecksum
                 * @brief calculate the checksum, and append it to message.
                 */
                void calculateChecksum();
    };
}

#endif // MULTIWII_HPP