#include <ArduinoFake.h>
#include <unity.h>
#include <multiwii.hpp>
#include <ld002_controller_factory.hpp>

#define DISABLE_STATUS_TEST

using namespace rrobot;
using namespace fakeit;

Mock<AbstractUsbInterface> mock;
std::vector<uint8_t> capturedOutput;

void setUp(void) {
    // set stuff up here
    When(Method(mock, available)).AlwaysReturn(1);
    When(Method(mock, begin).Using(9600)).Return();
    When(Method(mock, flush)).Return();
}

void tearDown(void) {
    // clean stuff up here
}


#ifdef NATIVE
void test_should_return_status(void) {
    capturedOutput.clear();
    When(Method(mock, read)).Return(101, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E);
    When(OverloadedMethod(mock, write, size_t(u_int8_t))).AlwaysDo(
        [](uint8_t c) {
            capturedOutput.push_back(c);
            return 1;
        }
    );

    Crc32 crc;
    Ld001ControllerFactory fact = Ld001ControllerFactory();
    RrMultiWii multiWii = RrMultiWii(crc, mock.get(), fact);
    multiWii.execute();

    TEST_ASSERT_EQUAL_UINT8(101, capturedOutput.at(0));
    TEST_ASSERT_EQUAL_UINT16((sizeof(uint16_t) * 3) + sizeof(uint32_t) + sizeof(uint8_t), highByte(capturedOutput.at(1)) | capturedOutput.at(2));
    
}

void test_should_return_sensor(void) {
    capturedOutput.clear();
    When(Method(mock, read)).Return(0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E);
    When(OverloadedMethod(mock, write, size_t(u_int8_t))).AlwaysDo(
        [](uint8_t c) {
            capturedOutput.push_back(c);
            return 1;
        }
    );

    Crc32 crc;
    Ld001ControllerFactory fact = Ld001ControllerFactory();
    RrMultiWii multiWii = RrMultiWii(crc, mock.get(), fact);
    multiWii.execute();

    TEST_ASSERT_EQUAL_UINT8(216, capturedOutput.at(0));
    // TEST_ASSERT_EQUAL_UINT16((sizeof(uint16_t) * 3) + sizeof(uint32_t) + sizeof(uint8_t), highByte(capturedOutput.at(1)) | capturedOutput.at(2));
    
}
#else
void test_should_return_status(void) {}
void test_should_return_sensor(void) {}
#endif


int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_should_return_status);
    RUN_TEST(test_should_return_sensor);
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