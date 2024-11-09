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
#include <stdlib.h>
#include <string.h>

#include "RrExceptions.hpp"
#include "commands.hpp"

using namespace std;

namespace rrobot {

enum class Direction_t : char {
    inbound = '<',
    outbound = '>',
    invalid = '!',
};

/**
 * @class MultiWii
 * @brief base class for MSP commands, this class should not be invoked directly.  It is used
 * as part of MSP commands. For serialization and desialization of ingress, and egress messages.
 */
class MultiWii {
   public:

    ~MultiWii();

    /**
     * @fn serialize
     * @brief serializes outbound messages, and sets all getters and setters.
     * @param command MSP command to send.
     * @param size size in bytes of payload.
     * @param payload payload to send.
     */
    uint8_t *serialize(const MspCommands, const uint8_t size, uint8_t *payload);

    /**
     * @fn deserialize
     * @brief called by factory to perform initial deserialization of inbound message. Evoked by
     * factory which perform the conversion to inbound message that can be processed.
     */
    int deserialize(uint8_t *, const uint8_t);

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
    void setPayload(uint8_t *, uint8_t);
    uint8_t *getPayload();

   private:
    // struct MspPackage_t _mspPackage;

    const char *_hdr = "$M";
    Direction_t _direction;
    uint8_t _size;
    MspCommands _type;
    uint8_t *_payload = NULL;
    uint8_t _checksum;

    // Size of package excluding payload
    const int pkgOffset = 6;

    /**
     * @fn calculateChecksum
     * @brief calculate the checksum, and append it to message.
     */
    uint8_t calculateChecksum();
    bool verifyHeader(uint8_t *packet);

    static constexpr Direction_t VALID_DIRECTIONS[] = {Direction_t::inbound, Direction_t::outbound};
    static constexpr int VALID_DIRECTIONS_CNT = 2;
    static constexpr MspCommands VALID_CMDS[] = {MspCommands::MSP_SONAR, MspCommands::MSP_STATUS};
};
}  // namespace rrobot

#endif  // MULTIWII_HPP