#ifndef BLE_HPP
#define BLE_HPP

#include <abstract_ble.hpp>

namespace rrobot {

#ifdef ARDUINO
class Ble : AbstractBle {
   public:
    void setContinuousMode() override {}
    void oneShotMode() override {}
    int begin() override { return 1; }
    void end() override {}
    int readAcceleration(float& x, float& y, float& z) override { return 1; }
    int accelerationAvailable() override { return 1; }
    float accelerationSampleRate() override { return 1.0; }
    int readGyroscope(float& x, float& y, float& z) override { return 1; }
    int gyroscopeAvailable() override { return 1; }
    float gyroscopeSampleRate() override { return 1.0; }
    int readMagneticField(float& x, float& y, float& z) { return 1; }
    int magneticFieldAvailable() { return 1; }
    float magneticFieldSampleRate() { return 1.0; }
};
#else
class Ble : AbstractBle {
   public:
    void setContinuousMode() override {}
    void oneShotMode() override {}
    int begin() override { return 1; }
    void end() override {}
    int readAcceleration(float& x, float& y, float& z) override { return 1; }
    int accelerationAvailable() override { return 1; }
    float accelerationSampleRate() override { return 1.0; }
    int readGyroscope(float& x, float& y, float& z) override { return 1; }
    int gyroscopeAvailable() override { return 1; }
    float gyroscopeSampleRate() override { return 1.0; }
    int readMagneticField(float& x, float& y, float& z) { return 1; }
    int magneticFieldAvailable() { return 1; }
    float magneticFieldSampleRate() { return 1.0; }
};
#endif
}  // namespace rrobot

#endif  // BLE_HPP