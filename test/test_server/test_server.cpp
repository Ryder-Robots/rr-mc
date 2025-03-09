#include <ArduinoFake.h>
#include <unity.h>
#include <rrpheader.hpp>
#include <serial_usb.hpp>

using namespace rrobot;
using namespace fakeit;

void test_serial_read() {
   
    When(Method(ArduinoFake(Serial), read)).Return('$');
    When(Method(ArduinoFake(Serial), read)).Return('M');
    When(Method(ArduinoFake(Serial), read)).Return(0);
    When(Method(ArduinoFake(Serial), read)).Return(0);
    When(Method(ArduinoFake(Serial), read)).Return(static_cast<uint8_t>(RrCommand::MSP_STATUS));
    When(Method(ArduinoFake(Serial), read)).Return(0);
    When(Method(ArduinoFake(Serial), read)).Return(0x1E);
    
    SerialUsb serialUsb = SerialUsb();
    uint8_t* data = serialUsb.read();

    TEST_ASSERT_EQUAL_UINT8('$', data[0]);
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