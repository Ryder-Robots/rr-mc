#include <Arduino.h>
#include "multiwii.hpp"
#include <unity.h>
#include <string.h>

using namespace rrobot;

const char* testPacket = "$M>1091234597";

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

void test_methods(void)
{
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
    char *charArray = reinterpret_cast<char*>(package);
    TEST_ASSERT_EQUAL(testPacket, charArray);

    free(package);
}

void setup()
{
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_methods);
    RUN_TEST(test_packet);
    UNITY_END();
}

void loop()
{
    UNITY_BEGIN();
    RUN_TEST(test_methods);
    RUN_TEST(test_packet);
    UNITY_END();
}
