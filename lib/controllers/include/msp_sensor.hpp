#ifndef MSP_SENSOR_HPP
#define MSP_SENSOR_HPP

#include <rrpheader.hpp>

namespace rrobot {
/**
 * Standard sensors not including ultrasonic.
 */
class MspSensor {
   public:
    void set_accAvail(int acc_avail) { _acc_avail = acc_avail; }

    int get_accAvail() { return _acc_avail; }

    void set_accX(float acc_x) { _acc_x = acc_x; }

    void set_accY(float acc_y) { _acc_y = acc_y; }

    void set_accZ(float acc_z) { _acc_z = acc_z; }

    float get_accX() { return _acc_x; }

    float get_accY() { return _acc_y; }

    float get_accZ() { return _acc_z; }

    void set_gyroAvail(int gyro_avail) { _gyro_avail = gyro_avail; }

    int get_gyroAvail() { return _gyro_avail; }

    void set_gyroX(float gyro_x) { _gyro_x = gyro_x; }

    void set_gyroY(float gyro_y) { _gyro_y = gyro_y; }

    void set_gyroZ(float gyro_z) { _gyro_z = gyro_z; }

    float get_gyroX() { return _gyro_x; }

    float get_gyroY() { return _gyro_y; }

    float get_gyroZ() { return _gyro_z; }

    void set_magAvail(int mag_avail) { _mag_avail = mag_avail; }

    int get_magAvail() { return _mag_avail; }

    void set_magX(float mag_x) { _mag_x = mag_x; }

    void set_magY(float mag_y) { _mag_y = mag_y; }

    void set_magZ(float mag_z) { _mag_z = mag_z; }

    float get_magX() { return _mag_x; }

    float get_magY() { return _mag_y; }

    float get_magZ() { return _mag_z; }

   private:
    int _acc_avail = 0;   // Accelometer available
    float _acc_x = 0;     // X coordinate
    float _acc_y = 0;     // Y coordinate
    float _acc_z = 0;     // Z coordinate
    int _gyro_avail = 0;  // Gyroscope available
    float _gyro_x = 0;
    float _gyro_y = 0;
    float _gyro_z = 0;
    int _mag_avail = 0;
    float _mag_x = 0;
    float _mag_y = 0;
    float _mag_z = 0;
};
}  // namespace rrobot

#endif  // MSP_SENSOR_HPP