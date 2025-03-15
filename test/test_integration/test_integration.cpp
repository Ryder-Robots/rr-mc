#include <ArduinoFake.h>
#include <unity.h>

#include <main.hpp>

using namespace rrobot;
using namespace fakeit;
// /**
//  *
//  * $M[direction][size][command][data][checksum]
//  */
Ld001ControllerFactory ctl;
SerialUsb serialUsb;

// put function declarations here:
void setup() {
    ArduinoFakeReset();
    ctl.setUp();
    serialUsb.begin(9600);
}

void teardown() { ctl.tearDown(); }

void loop() {
    MspShutdownController* shutdown =
        reinterpret_cast<MspShutdownController*>(ctl.retrieveEncoder(RrCommand::MSP_EXIT));

    if (shutdown->isShutdown()) {
        return;
    }

    if (serialUsb.available()) {
        uint8_t* ingres = serialUsb.read();
        RrController* encoder = ctl.retrieveEncoder(ingres);
        serialUsb.write(encoder->execute(ingres), encoder->encoder()->getSize());
        serialUsb.flush();
    }
}

// /**
//  * @fn main
//  * @brief
//  * main method added so that code can be compiled using native environment with library ArduinoFake
//  */
// int main() {
//   setup();
//   while(1) {
//     loop();
//   }
//   return 0;
// }

void test_integration(void) {
    When(Method(ArduinoFake(Serial), available)).Return(1);
    When(Method(ArduinoFake(Serial), flush)).AlwaysReturn();
    When(Method(ArduinoFake(Serial), read))
        .Return('$', 'M', 0, 0, static_cast<uint8_t>(RrCommand::MSP_STATUS), 0, 0x1E);
    loop();
}

int main(int argc, char** argv) {
    UNITY_BEGIN();
    RUN_TEST(test_integration);

    // Add more RUN_TEST calls for additional test functions
    return UNITY_END();
}