#ifndef RRCOMMANDS_HPP
#define RRCOMMANDS_HPP

#include <stdint.h>

namespace rrobot {

enum class RrCommand : uint8_t {
    MSP_UNSUPPORTED = 1,  // Not supported command (or incorrect)
    MSP_STATUS = 104,
    MSP_SENSOR = 216,
    MSP_EXIT = 217,  // inbound command, to signify that processor should shutdown.
};
}

#endif