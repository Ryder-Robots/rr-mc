#ifndef MAVAUTOPILOT_HPP
#define MAVAUTOPILOT_HPP

#include<stdint.h>

/**
 * @breif Reference https://mavlink.io/en/messages/common.html#MAV_AUTOPILOT_INVALID
 * 
 * Autopilot type / class. Set to MAV_AUTOPILOT_INVALID for components that are 
 * not flight controllers (e.g. ground stations, gimbals, etc.).
 */

enum MavAutoPilot : uint8_t {
    /**
     * @brief No valid autopilot, e.g. a GCS or other MAVLink component
     */
    MAV_AUTOPILOT_INVALID = 8, 
};

#endif // MAVAUTOPILOT_HPP