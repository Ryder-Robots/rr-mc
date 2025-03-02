#ifndef RRHEADER_HPP
#define RRHEADER_HPP

#include <stdint.h>


// MultiWii proposes small endian which is kinda weird.
#if defined(BYTE_ORDER) && BYTE_ORDER == LITTLE_ENDIAN

#define htons(X) X
#define htonl(X) X
#define ntohs(X) X
#define ntohl(X) X

// There is some weirdness going on here. Not sure why yet.
#else

#define PP_HTONS(x) ((uint16_t)((((x) & (uint16_t)0x00ffU) << 8) | (((x) & (uint16_t)0xff00U) >> 8)))
#define PP_NTOHS(x) PP_HTONS(x)
#define PP_HTONL(x) ((((x) & (uint32_t)0x000000ffUL) << 24) | \
                     (((x) & (uint32_t)0x0000ff00UL) <<  8) | \
                     (((x) & (uint32_t)0x00ff0000UL) >>  8) | \
                     (((x) & (uint32_t)0xff000000UL) >> 24))
#define PP_NTOHL(x) PP_HTONL(x)

#define htons(X) PP_HTONS(X)
#define htonl(X) PP_HTONL(X)
#define ntohs(X) PP_NTOHS(X)
#define ntohl(X) PP_NTOHL(X)

#endif

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
        MSP_STATUS = 104,
    };

    enum class RrMspSensorFlags : uint16_t {
        BARO  =0b000000000000001,  // Barometer
        MAG   =0b000000000000010,  // Magnometer
        GPS   =0b000000000000100,  // GPS
        SONAR =0b000000000001000,  // Ultrasonic
        CAMERA=0b000000000010000, // Camera available
    };

    enum RRP_STATUS : uint32_t {
        INITILIZING    = 1 << 0,  // indicates that the handler has been started but is not yet active
        ACTIVE         = 1 << 1,  // indicates that the handler is an active state, and ready to consume or produce.
        ERROR          = 1 << 2,  // indicates that an error has occured, and the handler will need to be reloaded.
        RELOADING      = 1 << 3,  // reloading after an error has occured.
        SHUTTING_DOWN  = 1 << 4, // indicates that system is now shutting down.
        TERMINATED     = 1 << 5, // handler has terminated.
    };
}

#endif