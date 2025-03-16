#include <ble.hpp>
#include <encoder_msp_sensor.hpp>

using namespace rrobot;

/*
 * _acc_avail int32
 * _acc_x float
 * _acc_y float
 * _acc_z float
 * _gyro_avail int32
 * _gyro_x float
 * _gyro_y float
 * _gyro_z float
 * _mag_avail int32
 * _mag__x float
 * _mag__y float
 * _mag__z float
 */
uint8_t* EncoderMspSensor::encode(void* data) {
    uint8_t* encoded = static_cast<uint8_t*>(malloc(getSize()));
    MspSensor* obj = static_cast<MspSensor*>(data);
    int pos = splitUint32(obj->get_accAvail(), encoded, 0);
    pos = splitFloat(obj->get_accX(), encoded, pos);
    pos = splitFloat(obj->get_accY(), encoded, pos);
    pos = splitFloat(obj->get_accZ(), encoded, pos);
    pos = splitUint32(obj->get_gyroAvail(), encoded, pos);
    pos = splitFloat(obj->get_gyroX(), encoded, pos);
    pos = splitFloat(obj->get_gyroY(), encoded, pos);
    pos = splitFloat(obj->get_gyroZ(), encoded, pos);
    pos = splitUint32(obj->get_magAvail(), encoded, pos);
    pos = splitFloat(obj->get_magX(), encoded, pos);
    pos = splitFloat(obj->get_magY(), encoded, pos);
    pos = splitFloat(obj->get_magZ(), encoded, pos);

    return encoded;
}

/*
 * There is not need to decode input with MSP_SENSOR header, this is done strictly
 * for compliance.
 */
void* EncoderMspSensor::decode(uint8_t* data) { return nullptr; }