#include <ArduinoFake.h>
#include <unity.h>
#include <abstract_ble.hpp>

using namespace rrobot;

class MockAbstractBle : public AbstractBle {
    public:
    void setContinuousMode() override {}
    void oneShotMode() override {}
    int begin() override {return 1;}
    void end() override {}
    int readAcceleration(float& x, float& y, float& z) override { return 1;}
    int accelerationAvailable() override {return 1;}
    float accelerationSampleRate() override {return 1.0;}
    int readGyroscope(float& x, float& y, float& z) override {return 1;}
    int gyroscopeAvailable() override {return 1;}
    float gyroscopeSampleRate() override {return 1.0;}
    int readMagneticField(float& x, float& y, float& z) {return 1;}
    int magneticFieldAvailable() {return 1;}
    float magneticFieldSampleRate() {return 1.0;}
};

void test_readAcceleration(void) {
}


int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_readAcceleration);
    return UNITY_END();
}

#ifdef ARDUINO
void setup() {
    delay(2000);
    ArduinoFakeReset();
    runUnityTests();
}

void loop() {}
#else
int main(void) {
    ArduinoFakeReset();
    return runUnityTests(); 
}
#endif