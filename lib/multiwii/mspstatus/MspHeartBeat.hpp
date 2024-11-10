#ifndef MSPHEARTBEAT_HPP
#define MSPHEARTBEAT_HPP

#include <stdint.h>
#include <stddef.h>
#include <Arduino.h>

#include <common/MavAutoPilot.hpp>
#include <common/MavMode.hpp>
#include <common/MavState.hpp>
#include <common/MavType.hpp>

#include <multiwii.hpp>

/**
 * @class MspHeartBeat
 * @brief The heartbeat message shows that a system or component is present and responding. The type and autopilot
 * fields (along with the message component id), allow the receiving system to treat further messages from this system
 * appropriately (e.g. by laying out the user interface based on the autopilot). This microservice is documented at
 * https://mavlink.io/en/services/heartbeat.html
 */
namespace rrobot {
class MspHeartBeat {
   public:
    /**
     * @fn MspHeartBeat
     * @brief class constructor
     * @param base_mode System mode bitmap.
     * @param custom_mode set ultra sonic(s), this 
     */
    MspHeartBeat(MavMode base_mode, uint32_t custom_mode, MavState system_status):
        _base_mode(base_mode),
        _custom_mode(custom_mode),
        _system_status(system_status) {}
    ~MspHeartBeat() {}

    size_t getPacketSz();

    /**
     * @fn serialize
     * @brief serialize request.
     * 
     */
    uint8_t *serialize();
   private:
    const MavType      _type = MavType::MAV_TYPE_GROUND_ROVER;
    const MavAutoPilot _autopilot = MavAutoPilot::MAV_AUTOPILOT_INVALID;
    MavMode _base_mode = MavMode::MAV_MODE_PREFLIGHT;

    /**
     * A bitfield for use for autopilot-specific flags, this
     * can be used for output from utra-sonics.
     */
    uint32_t _custom_mode = 0;
    MavState _system_status = MavState::MAV_STATE_STANDBY;

    // compatible with MAVLink 2
    const uint8_t _mavlink_version = 200;
};
}  // namespace rrobot

#endif