#include <ArduinoFake.h>
#include <unity.h>
#include <multiwii.hpp>
#include <ld002_controller_factory.hpp>

#define DISABLE_STATUS_TEST

using namespace rrobot;
using namespace fakeit;

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

#ifndef DISABLE_STATUS_TEST
#ifdef NATIVE
void test_should_return_status(void) {
    std::vector<uint8_t> capturedOutput;
    When(OverloadedMethod(ArduinoFake(Serial), write, size_t(uint8_t))).Return(1);
    When(Method(ArduinoFake(Serial), read)).Return(0x68, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E);
    When(Method(ArduinoFake(Serial), available)).AlwaysReturn(1);

    RrMultiWii multiWii = RrMultiWii(Crc32(), new Ld001ControllerFactory());
    multiWii.execute();

    uint8_t c = capturedOutput.front();
    TEST_ASSERT_EQUAL_UINT8(0x68, c);
    
}
#endif
#else
void test_should_return_status(void) {}
#endif


int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_should_return_status);
    return UNITY_END();
}

#ifdef ARDUINO
void setup() {
    delay(2000);
    runUnityTests();
}

void loop() {}
#else
int main(void) { return runUnityTests(); }
#endif