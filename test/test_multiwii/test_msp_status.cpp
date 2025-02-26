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

void test_common_functions() {
    EncoderMspStatus* encoder = new EncoderMspStatus();
    uint8_t* data = reinterpret_cast<uint8_t*>(malloc(sizeof(uint32_t)));
    int pos = 0;
    encoder->splitUint32(2765, data, 0);
    uint32_t v = encoder->decodeUint32(data, pos);

    TEST_ASSERT_EQUAL(4, pos);
    TEST_ASSERT_EQUAL(2765, v);

    encoder->splitUint16(213, data, pos);
    TEST_ASSERT_EQUAL(213, encoder->decodeUint16(data, pos));
    
}

void test_should_encode() {
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
    mspStatus.set_current_set(0);

    Crc32 crc;
    EncoderMspStatus* encoder = new EncoderMspStatus();

    RrMultiWii multiWii(encoder, crc);
    uint8_t* encoded = multiWii.encode(static_cast<void *>(&mspStatus));
    

    TEST_ASSERT_EQUAL('$', encoded[0]);
    TEST_ASSERT_EQUAL('M', encoded[1]);
    uint16_t sz = (static_cast<uint16_t>(encoded[2]) << 8) | encoded[3];
    TEST_ASSERT_EQUAL((sizeof(uint16_t) * 3) + sizeof(uint32_t) + sizeof(uint8_t), sz);
    TEST_ASSERT_EQUAL(RrCommand::MSP_STATUS, encoded[4]);

    // cycletime [5, 6]
    TEST_ASSERT_EQUAL(100, (static_cast<uint16_t>(encoded[5]) << 8) | encoded[6]);

    // error count [7, 8]
    TEST_ASSERT_EQUAL(2, (static_cast<uint16_t>(encoded[7]) << 8) | encoded[8]);

    // sensors [9, 10]
    TEST_ASSERT_EQUAL(
        static_cast<uint16_t>(RrMspSensorFlags::BARO) | 
        static_cast<uint16_t>(RrMspSensorFlags::GPS)  |
        static_cast<uint16_t>(RrMspSensorFlags::MAG)  |
        static_cast<uint16_t>(RrMspSensorFlags::SONAR),
        
        (static_cast<uint16_t>(encoded[9]) << 8) | encoded[10]
    );

    // // flag [11, 12, 13, 14]
    // TEST_ASSERT_EQUAL(
    //     static_cast<uint32_t>(RRP_STATUS::ACTIVE), 
    //     (static_cast<uint32_t>(encoded[11] << 24)  | encoded[12] << 16 | encoded[13] << 8 | encoded[14])
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
    RUN_TEST(test_common_functions);
    // Add more RUN_TEST calls for additional test functions
    return UNITY_END();
}
