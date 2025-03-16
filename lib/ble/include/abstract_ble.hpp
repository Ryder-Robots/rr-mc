#ifndef ABSTRACT_BLE
#define ABSTRACT_BLE

namespace rrobot {

/**
 * @class AbstractBle
 * @brief
 * interface to BoshSensor, in native mode this can be used to fake expected results.
 * In Arduino mode it will interface to MBED chipset.
 */
class AbstractBle {
   public:
    virtual void setContinuousMode() = 0;
    virtual void oneShotMode() = 0;

    virtual int begin() = 0;
    virtual void end() = 0;

    // Accelerometer
    virtual int readAcceleration(float &x, float &y, float &z) = 0;  // Results are in G (earth gravity).
    virtual int accelerationAvailable() = 0;                         // Number of samples in the FIFO.
    virtual float accelerationSampleRate() = 0;                      // Sampling rate of the sensor.

    // Gyroscope
    virtual int readGyroscope(float &x, float &y, float &z) = 0;  // Results are in degrees/second.
    virtual int gyroscopeAvailable() = 0;                         // Number of samples in the FIFO.
    virtual float gyroscopeSampleRate() = 0;                      // Sampling rate of the sensor.

    // Magnetometer
    virtual int readMagneticField(float &x, float &y, float &z) = 0;  // Results are in uT (micro Tesla).
    virtual int magneticFieldAvailable() = 0;                         // Number of samples in the FIFO.
    virtual float magneticFieldSampleRate() = 0;                      // Sampling rate of the sensor.
};
}  // namespace rrobot

#endif  // ABSTRACT_BLE