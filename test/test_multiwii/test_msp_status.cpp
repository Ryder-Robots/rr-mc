#ifdef NATIVE

#define htons(X) X
#define htonl(X) X
#define ntohs(X) X

#endif

#include <unity.h>
#include <ArduinoFake.h>
#include <multiwii.hpp>
#include <msp_status.hpp>
#include <encoder_msp_status.hpp>

using namespace rrobot;

void test_should_encode() {
    // Your test code here
    MspStatus mspStatus;

    mspStatus.set_cycletime(100);
    mspStatus.set_i2c_errors_count(2);
    mspStatus.set_sensor(
        static_cast<uint16_t>(RrMspSensorFlags::BARO) | 
        static_cast<uint16_t>(RrMspSensorFlags::GPS)  |
        static_cast<uint16_t>(RrMspSensorFlags::MAG)  |
        static_cast<uint16_t>(RrMspSensorFlags::SONAR)
    );
    mspStatus.set_flag(RRP_STATUS::ACTIVE);

    Crc32 crc;
    EncoderMspStatus* encoder = new EncoderMspStatus();

    RrMultiWii multiWii(encoder, crc);
    uint8_t* encoded = multiWii.encode(static_cast<void *>(&mspStatus));
    
    //std::string s(reinterpret_cast<char*>(encoded));
    //Serial.println(s);

    TEST_ASSERT_EQUAL(1, encoded[0]);
}

void setUp(void) {
    ArduinoFakeReset();
}

void tearDown(void) {
    // Clean up code if needed
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_should_encode);
    // Add more RUN_TEST calls for additional test functions
    return UNITY_END();
}
