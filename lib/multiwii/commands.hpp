#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <stdint.h>

namespace rrobot {
    enum class MspCommands : uint8_t {
        MSP_STATUS = 101,
        MSP_SONAR  = 109, // Note that 109 is officially defined as 
                          // as MSP_ALTITUDE but is a defacto standard for 
                          // the undefined status MSP_SONAR
    };
}

#endif // COMMANDS_HPP