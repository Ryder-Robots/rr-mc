#ifndef RRHEADER_HPP
#define RRHEADER_HPP

#include <stdint.h>

namespace rrobot {
     /**
     * @class RrDirection
     * @brief
     * Direction on request
     */
    enum class RrDirection : char {
        MWC_TO    = '<',
        MWC_FROM  = '>',
        MWC_ERROR = '!'
    };

    enum class RrCommand : uint8_t {
        MSP_IDENT  = 100,
    };
}

#endif