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
    

    TEST_ASSERT_EQUAL('$', encoded[0]);
    TEST_ASSERT_EQUAL('M', encoded[1]);
    uint16_t sz = (static_cast<uint16_t>(encoded[2]) << 8) | encoded[3];
    TEST_ASSERT_EQUAL((sizeof(uint16_t) * 4) + sizeof(uint8_t), sz);
    TEST_ASSERT_EQUAL(RrCommand::MSP_STATUS, encoded[4]);

    // cycletime
    TEST_ASSERT_EQUAL(100, (static_cast<uint16_t>(encoded[5]) << 8) | encoded[6]);

    // error count
    // TEST_ASSERT_EQUAL(2, (static_cast<uint16_t>(encoded[6]) << 8) | encoded[7]);

    // sensors
    // TEST_ASSERT_EQUAL(
    //     static_cast<uint16_t>(RrMspSensorFlags::BARO) | 
    //     static_cast<uint16_t>(RrMspSensorFlags::GPS)  |
    //     static_cast<uint16_t>(RrMspSensorFlags::MAG)  |
    //     static_cast<uint16_t>(RrMspSensorFlags::SONAR),
        
    //     (static_cast<uint16_t>(encoded[8]) << 8) | encoded[9]
    // );
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
