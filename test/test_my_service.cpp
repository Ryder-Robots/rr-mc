#include <unity.h>
#include <ArduinoFake.h>

void test_example_function() {
    // Your test code here
    TEST_ASSERT_EQUAL(1, 1);
}

void setUp(void) {
    ArduinoFakeReset();
}

void tearDown(void) {
    // Clean up code if needed
}

int main(int argc, char **argv) {
    UNITY_BEGIN();
    RUN_TEST(test_example_function);
    // Add more RUN_TEST calls for additional test functions
    return UNITY_END();
}
