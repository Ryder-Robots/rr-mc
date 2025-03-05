#ifndef BLE_HPP
#define BLE_HPP

#include <abstract_ble.hpp>

#ifndef NATIVE
#include <Arduino_BMI270_BMM150.h>
#endif

namespace rrobot {

#ifdef NATIVE
class Ble : AbstractBle {
   public:
    void setContinuousMode() override {}

    void oneShotMode() override {}

    int begin() override { return 1; }

    void end() override {}

    int readAcceleration(float& x, float& y, float& z) override {
        x = 1;
        y = 2;
        z = 3;
        return 2; 
    }

    int accelerationAvailable() override { return 0x01; }

    float accelerationSampleRate() override { return 104.0; }

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
    void setContinuousMode() override {
        IMU.setContinuousMode();
    }
    
    void oneShotMode() override {}
    
    int begin() override { 
        return IMU.begin(); 
    }
    
    void end() override {
        IMU.end();
    }

    int readAcceleration(float& x, float& y, float& z) override { 
        return IMU.readAcceleration(x, y, z);
    }

    int accelerationAvailable() override { 
        return IMU.accelerationAvailable();
    }


    float accelerationSampleRate() override { 
        return IMU.accelerationSampleRate();
    }


    int readGyroscope(float& x, float& y, float& z) override { 
        return IMU.readGyroscope(x, y, z);
    }


    int gyroscopeAvailable() override { 
        return IMU.gyroscopeAvailable();
    }

    float gyroscopeSampleRate() override { 
        return IMU.gyroscopeSampleRate();
    }

    int readMagneticField(float& x, float& y, float& z) { 
        return IMU.readMagneticField(x, y, z);
    }

    int magneticFieldAvailable() { 
        return IMU.magneticFieldAvailable();
    }

    float magneticFieldSampleRate() { 
        return IMU.magneticFieldSampleRate();
    }
};
#endif
}  // namespace rrobot

#endif  // BLE_HPP