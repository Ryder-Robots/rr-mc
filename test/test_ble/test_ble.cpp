#include <unity.h>
#include <ble.hpp>

using namespace rrobot;


void test_readAcceleration(void) {
    Ble ble = Ble();
    TEST_ASSERT_EQUAL_INT(1, ble.begin());
    float x = 0, y = 0, z = 0;
    TEST_ASSERT_EQUAL_INT(2, ble.readAcceleration(x, y, z));
    TEST_ASSERT_EQUAL_FLOAT(1, x);
    TEST_ASSERT_EQUAL_FLOAT(2, y);
    TEST_ASSERT_EQUAL_FLOAT(3, z);
}

void test_accelerationAvailable(void) {
    Ble ble = Ble();
    TEST_ASSERT_EQUAL_INT(1, ble.begin());
    TEST_ASSERT_EQUAL_INT(0x01, ble.accelerationAvailable());
}

void test_accelerationSampleRate(void) {
    Ble ble = Ble();
    TEST_ASSERT_EQUAL_INT(1, ble.begin());
    TEST_ASSERT_EQUAL_FLOAT(104.0, ble.accelerationSampleRate());
}


int runUnityTests(void) {
    UNITY_BEGIN();
    RUN_TEST(test_readAcceleration);
    RUN_TEST(test_accelerationAvailable);
    return UNITY_END();
}

#ifdef ARDUINO
void setup() {
    delay(2000);
    runUnityTests();
}

void loop() {}
#else
int main(void) {
    return runUnityTests(); 
}
#endif