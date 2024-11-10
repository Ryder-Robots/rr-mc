#ifndef MAVMODE_HPP
#define MAVMODE_HPP

#include <stdint.h>

/**
 * @brief These defines are predefined OR-combined mode flags. There is no need to use values from this enum,
 *  but it simplifies the use of the mode flags. Note that manual input is enabled in all modes as a 
 *  safety override.
 */

namespace rrobot {
    enum MavMode : uint8_t {
        /**
         * @brief System is not ready to fly, booting, calibrating, etc. No flag is set.
         */
        MAV_MODE_PREFLIGHT = 0,

        /**
         * @brief System is allowed to be active, under manual (RC) control, no stabilization
         */
        MAV_MODE_MANUAL_DISARMED = 64,

        /**
         * @brief UNDEFINED mode. This solely depends on the autopilot - use with caution, 
         * intended for developers only.
         */
        MAV_MODE_TEST_DISARMED = 66,

        /**
         * @brief System is allowed to be active, under assisted RC control.
         */
        MAV_MODE_STABILIZE_DISARMED = 88,

        /**
         * @brief System is allowed to be active, under autonomous control, manual setpoint
         */
        MAV_MODE_GUIDED_DISARMED = 88,

        /**
         * @brief System is allowed to be active, under autonomous control and navigation (the trajectory is 
         * decided onboard and not pre-programmed by waypoints)
         */
        MAV_MODE_AUTO_DISARMED = 92,

        /**
         * @brief System is allowed to be active, under manual (RC) control, no stabilization
         */
        MAV_MODE_MANUAL_ARMED = 192,

        /**
         * @brief UNDEFINED mode. This solely depends on the autopilot - use with caution, 
         * intended for developers only.
         */
        MAV_MODE_TEST_ARMED = 194,

        /**
         * @brief System is allowed to be active, under assisted RC control.
         */
        MAV_MODE_STABILIZE_ARMED = 208,

        /**
         * @brief System is allowed to be active, under autonomous control, manual setpoint
         */
        MAV_MODE_GUIDED_ARMED = 216,

        /**
         * @brief System is allowed to be active, under autonomous control and navigation 
         * (the trajectory is decided onboard and not pre-programmed by waypoints)
         */
        MAV_MODE_AUTO_ARMED = 220,
    };
}

#endif