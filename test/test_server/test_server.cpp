#include <ArduinoFake.h>
#include <unity.h>
#include <rrpheader.hpp>
#include <serial_usb.hpp>

using namespace rrobot;
using namespace fakeit;

void test_serial_read() {
   
    When(Method(ArduinoFake(Serial), read)).Return('$', 'M', 0, 0, static_cast<uint8_t>(RrCommand::MSP_STATUS), 0, 0x1E);
    When(Method(ArduinoFake(Serial), available)).Return(1);
    
    SerialUsb serialUsb = SerialUsb();
    uint8_t* data = serialUsb.read();

    TEST_ASSERT_EQUAL_UINT8('$', data[0]);
    TEST_ASSERT_EQUAL_UINT8('M', data[1]);
    TEST_ASSERT_EQUAL_UINT8(0, data[2]);
    TEST_ASSERT_EQUAL_UINT8(0, data[3]);
    TEST_ASSERT_EQUAL(static_cast<uint8_t>(RrCommand::MSP_STATUS), data[4]);
    TEST_ASSERT_EQUAL_UINT8(0, data[5]);
    TEST_ASSERT_EQUAL_UINT8( 0x1E, data[6]);
    TEST_ASSERT_EQUAL(1, serialUsb.available());
}

void setUp(void) {
    ArduinoFakeReset();
}

void tearDown(void) {
    // Clean up code if needed
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_serial_read);

    // Add more RUN_TEST calls for additional test functions
    return UNITY_END();
}