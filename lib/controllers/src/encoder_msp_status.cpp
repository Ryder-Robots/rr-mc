#include <encoder_msp_status.hpp>

using namespace rrobot;
/*
 *  variable order is:
 *   uint16_t _cycletime          [0, 1]
 *   uint16_t _i2c_errors_count   [2, 3]
 *   uint16_t _sensor             [4, 5]
 *   uint32_t _flag;              [6, 7, 8, 9]
 *   uint8_t  _current_set;       [10]
 */
uint8_t* EncoderMspStatus::encode(void* data) {
    uint8_t* encoded = static_cast<uint8_t*>(malloc(getSize()));
    MspStatus* obj = static_cast<MspStatus*>(data);
    int pos = splitUint16(obj->get_cycletime(), encoded, 0);
    pos = splitUint16(obj->get_i2c_errors_count(), encoded, pos);
    pos = splitUint16(obj->get_sensor(), encoded, pos);
    pos = splitUint32(obj->get_flag(), encoded, pos);
    encoded[pos] = obj->get_current_set();
    return encoded;
}

void* EncoderMspStatus::decode(uint8_t* data) {
    MspStatus* decoded = new MspStatus();
    int pos = 0;
    decoded->set_cycletime(decodeUint16(data, pos));
    decoded->set_i2c_errors_count(decodeUint16(data, pos));
    decoded->set_sensor(decodeUint16(data, pos));
    decoded->set_flag(static_cast<RRP_STATUS>(decodeUint32(data, pos)));
    decoded->set_current_set(data[pos]);

    return static_cast<void*>(decoded);
}