#include <ArduinoFake.h>
#include <unity.h>

#include <controller_msp_status.hpp>
#include <limits>

using namespace rrobot;


void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_set_cycletime(void) {
    MspStatusController controller;

    // Test normal value
    controller.set_cycletime(1000);
    controller.set_i2c_errors_count(500);
    MspStatus *result =
        reinterpret_cast<MspStatus *>(controller.execute(reinterpret_cast<void *>(RrCommand::MSP_STATUS)));
    TEST_ASSERT_EQUAL_UINT16(1000, result->get_cycletime());
}

void test_set_i2c_errors_count(void) {
    MspStatusController controller;

    // Test normal value
    controller.set_i2c_errors_count(500);
    MspStatus *result =
        reinterpret_cast<MspStatus *>(controller.execute(reinterpret_cast<void *>(RrCommand::MSP_STATUS)));
    TEST_ASSERT_EQUAL_UINT16(500, result->get_i2c_errors_count());
}

void test_set_flag(void) {
    MspStatusController controller;
    MspStatus *result =
        reinterpret_cast<MspStatus *>(controller.execute(reinterpret_cast<void *>(RrCommand::MSP_STATUS)));

    controller.set_flag(RRP_STATUS::ACTIVE);
    result = reinterpret_cast<MspStatus *>(controller.execute(reinterpret_cast<void *>(RrCommand::MSP_STATUS)));
    TEST_ASSERT_EQUAL(RRP_STATUS::ACTIVE, result->get_flag());
}

void test_set_current_set(void) {
    MspStatusController controller;

    // Test normal value
    controller.set_current_set(5);
    MspStatus *result =
        reinterpret_cast<MspStatus *>(controller.execute(reinterpret_cast<void *>(RrCommand::MSP_STATUS)));
    TEST_ASSERT_EQUAL_UINT8(5, result->get_current_set());
}

void test_all_parameters(void) {
    MspStatusController controller;
    controller.set_cycletime(2000);
    controller.set_i2c_errors_count(300);
    controller.set_flag(RRP_STATUS::ACTIVE);
    controller.set_current_set(7);

    MspStatus *result =
        reinterpret_cast<MspStatus *>(controller.execute(reinterpret_cast<void *>(RrCommand::MSP_STATUS)));

    TEST_ASSERT_EQUAL_UINT16(2000, result->get_cycletime());
    TEST_ASSERT_EQUAL_UINT16(300, result->get_i2c_errors_count());
    TEST_ASSERT_EQUAL(RRP_STATUS::ACTIVE, result->get_flag());
    TEST_ASSERT_EQUAL_UINT8(7, result->get_current_set());
}

void test_command_execute(void) {
    MspStatusController controller;
    controller.set_cycletime(1000);
    controller.set_i2c_errors_count(500);
    controller.set_flag(RRP_STATUS::ACTIVE);
    controller.set_current_set(5);
    uint8_t data[] = {'$', 'M', 0, 0, static_cast<uint8_t>(RrCommand::MSP_STATUS), 0, 0x1E};
    MspStatus* response = static_cast<MspStatus*>(controller.execute(data));

    TEST_ASSERT_EQUAL_UINT16(1000, response->get_cycletime());
    TEST_ASSERT_EQUAL_UINT16(500, response->get_i2c_errors_count());
    TEST_ASSERT_EQUAL(RRP_STATUS::ACTIVE, response->get_flag());
    TEST_ASSERT_EQUAL_UINT8(5, response->get_current_set());
}

int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_set_cycletime);
    RUN_TEST(test_set_i2c_errors_count);
    RUN_TEST(test_set_flag);
    RUN_TEST(test_set_current_set);
    RUN_TEST(test_all_parameters);
    RUN_TEST(test_command_execute);
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