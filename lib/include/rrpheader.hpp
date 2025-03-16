#ifndef RRHEADER_HPP
#define RRHEADER_HPP
#include <Arduino.h>
#include <stdint.h>


namespace rrobot {
    enum class RrError : uint8_t {
        MSP_OK                = 0,
        MSP_CMD_NOT_SUPPORTED = 1, // unsupported command 
        MSP_SIZE_MISSMATCH    = 2, // size does match size of controller.
        MSP_INVALID_DATA      = 3, // data is invalid
    };

    enum class RrCommand : uint8_t {
        MSP_UNSUPPORTED = 0, // Not supported command (or incorrect)
        MSP_STATUS = 104,
        MSP_SENSOR = 216,
        MSP_EXIT   = 217, // inbound command, to signify that processor should shutdown.
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