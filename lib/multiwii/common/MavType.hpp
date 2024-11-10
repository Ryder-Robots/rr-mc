#ifndef MAVTYPE_HPP
#define MAVTYPE_HPP

#include <stdint.h>

/**
 * @breif MAVLINK component type reported in HEARTBEAT message. Flight controllers must report the type of the vehicle on which they are mounted 
 * (e.g. MAV_TYPE_OCTOROTOR). All other components must report a value appropriate for their type (e.g. a camera must use MAV_TYPE_CAMERA).
 */
namespace rrobot {
    enum MavType  : uint8_t {

        MAV_TYPE_GENERIC = 0,
        MAV_TYPE_QUADROTOR = 2,
        MAV_TYPE_GROUND_ROVER = 10,
        MAV_TYPE_SURFACE_BOAT = 11,
        MAV_TYPE_SUBMARINE = 12
    };
}

#endif