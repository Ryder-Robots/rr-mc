#ifndef RRERROR_HPP
#define RRERROR_HPP

#include <stdint.h>

namespace rrobot {
    enum class RrError : uint8_t {
        MSP_OK                = 0,
        MSP_CMD_NOT_SUPPORTED = 1, // unsupported command 
        MSP_SIZE_MISSMATCH    = 2, // size does match size of controller.
        MSP_INVALID_DATA      = 3, // data is invalid
    };
}

#endif