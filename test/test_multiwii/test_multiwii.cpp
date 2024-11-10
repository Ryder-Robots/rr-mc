#include <Arduino.h>
#include <string.h>
#include <unity.h>

#include <multiwii.hpp>
#include <mspstatus/MspHeartBeat.hpp>


using namespace rrobot;

const char *testPacket = "$ M > 109 5 1 2 3 4 5 97";

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_methods(void) {
    MultiWii msp = MultiWii();
    uint8_t *arr = (uint8_t *)malloc(5 * sizeof(uint8_t));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    uint8_t *package = msp.serialize(MspCommands::MSP_SONAR, 5, arr);

    // TEST_ASSERT_EQUAL(MspCommands::MSP_STATUS, msp.getType());
    TEST_ASSERT_EQUAL(MspCommands::MSP_SONAR, msp.getType());
    TEST_ASSERT_EQUAL(Direction_t::outbound, msp.getDirection());

    free(package);
}

void test_packet(void) {
    MultiWii msp = MultiWii();
    uint8_t *arr = (uint8_t *)malloc(5 * sizeof(uint8_t));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    uint8_t *package = msp.serialize(MspCommands::MSP_SONAR, 5, arr);

    TEST_ASSERT_EQUAL(arr[0], msp.getPayload()[0]);
    TEST_ASSERT_EQUAL(arr[1], msp.getPayload()[1]);
    TEST_ASSERT_EQUAL(arr[2], msp.getPayload()[2]);
    TEST_ASSERT_EQUAL(arr[3], msp.getPayload()[3]);
    TEST_ASSERT_EQUAL(arr[4], msp.getPayload()[4]);

    free(package);
}

void test_desialization(void) {
    uint8_t *arr = (uint8_t *)malloc(5 * sizeof(uint8_t));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    MultiWii msp1 = MultiWii();
    uint8_t *ingres = msp1.serialize(MspCommands::MSP_SONAR, 5, arr);

    MultiWii msp2 = MultiWii();
    int status = msp2.deserialize(ingres, 11);
    TEST_ASSERT_EQUAL(0, status);

    TEST_ASSERT_EQUAL(MspCommands::MSP_SONAR, msp2.getType());
    TEST_ASSERT_EQUAL(Direction_t::outbound, msp2.getDirection());
    TEST_ASSERT_EQUAL(arr[0], msp2.getPayload()[0]);
    TEST_ASSERT_EQUAL(arr[1], msp2.getPayload()[1]);
    TEST_ASSERT_EQUAL(arr[2], msp2.getPayload()[2]);
    TEST_ASSERT_EQUAL(arr[3], msp2.getPayload()[3]);
    TEST_ASSERT_EQUAL(arr[4], msp2.getPayload()[4]);

    free(ingres);
}


void test_serialize_heartbeat(void) {
    MspHeartBeat heartBeat = MspHeartBeat(MavMode::MAV_MODE_PREFLIGHT, 0, MavState::MAV_STATE_STANDBY);
    uint8_t* packet = heartBeat.serialize();

    TEST_ASSERT_EQUAL('$', static_cast<char>(packet[0]));
    TEST_ASSERT_EQUAL('M', static_cast<char>(packet[1]));
    TEST_ASSERT_EQUAL('>', static_cast<char>(packet[2]));
    TEST_ASSERT_EQUAL((sizeof(uint8_t) * 5) + sizeof(uint32_t), static_cast<int>(packet[3]));
    TEST_ASSERT_EQUAL(MspCommands::MSP_STATUS, static_cast<uint8_t>(packet[4]));
    TEST_ASSERT_EQUAL(MAV_TYPE_GROUND_ROVER, static_cast<MavType>(packet[5]));
    TEST_ASSERT_EQUAL(MAV_AUTOPILOT_INVALID, static_cast<MavAutoPilot>(packet[6]));
    TEST_ASSERT_EQUAL(MAV_MODE_PREFLIGHT, static_cast<MavMode>(packet[7]));
    TEST_ASSERT_EQUAL(MAV_STATE_STANDBY, static_cast<MavState>(packet[12]));
}

void setup() {
    delay(1000);

    UNITY_BEGIN();
    RUN_TEST(test_methods);
    RUN_TEST(test_packet);
    RUN_TEST(test_desialization);
    RUN_TEST(test_serialize_heartbeat);
    UNITY_END();
}

void loop() {
    UNITY_BEGIN();
    UNITY_END();
}
