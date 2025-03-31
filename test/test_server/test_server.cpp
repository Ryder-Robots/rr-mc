#include <unity.h>
#include <Arduino.h>
#include <serial_usb.hpp>
#include <rrpheader.hpp>

using namespace rrobot;
using namespace fakeit;

void test_serial_read() {
   
    When(Method(ArduinoFake(Serial), read)).Return(101, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1E);
    When(Method(ArduinoFake(Serial), available)).Return(1);
    
    SerialUsb serialUsb = SerialUsb();
    uint8_t* data = reinterpret_cast<uint8_t*>(malloc(sizeof(uint8_t) * 5));
    
    uint8_t c = 0;
    int i = 0;
    while (c != 0x1E) {
        c = serialUsb.read();
        data[i++] = c;
    }
    

    TEST_ASSERT_EQUAL_UINT8(static_cast<uint8_t>(RrCommand::MSP_STATUS), data[0]);
    // size is 0
    TEST_ASSERT_EQUAL_UINT16(0, (data[1] << 8) | data[2]);
    // CRC is 0 (no data)
    TEST_ASSERT_EQUAL_UINT32(0, (data[3] << 24) | (data[4] << 16) | (data[5] << 8) | data[6]);
    // Termination char
    TEST_ASSERT_EQUAL_UINT8(0x01E, data[7]);
    free(data);
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

    return UNITY_END();
}