#include <mspstatus/MspHeartBeat.hpp>


/**
 * Heart Beat implementation.
 */
using namespace rrobot;
using namespace std;

constexpr size_t PAYLOAD_SZ = (sizeof(uint8_t) * 5) + sizeof(uint32_t);

uint8_t* MspHeartBeat::serialize() {
    uint8_t* payload = reinterpret_cast<uint8_t *>(malloc(PAYLOAD_SZ));
    payload[0] = _type;
    payload[1] = _autopilot;
    payload[2] = _base_mode;
    
    payload[3] = _custom_mode & 0xFF;         
    payload[4] = (_custom_mode >> 8) & 0xFF;  
    payload[5] = (_custom_mode >> 16) & 0xFF;
    payload[6] = (_custom_mode >> 24) & 0xFF; 

    payload[7] = _system_status;
    payload[8] = _mavlink_version;

    MultiWii msp = MultiWii();
    uint8_t* packet = msp.serialize(MspCommands::MSP_STATUS, PAYLOAD_SZ, payload);
    free(payload);
    return packet;
}