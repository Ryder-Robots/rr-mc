#include <main.hpp>

using namespace rrobot;
/**
 * 
 * $M[direction][size][command][data][checksum]
 */
Ld001ControllerFactory ctl;
SerialUsb serialUsb;

// put function declarations here:
void setup() {
  ctl.setUp();
  serialUsb.begin(9600);
}

void teardown() {
  ctl.tearDown();
}

void loop() {
  MspShutdownController* shutdown = reinterpret_cast<MspShutdownController*>(ctl.retrieveEncoder(RrCommand::MSP_EXIT));

  if(shutdown->isShutdown()) {
    teardown();
  }
  
  if (serialUsb.available()) {
    uint8_t* ingres = serialUsb.read();
    RrController*encoder = ctl.retrieveEncoder(ingres);

    serialUsb.write(encoder->execute(ingres), encoder->encoder()->getSize());
    serialUsb.flush();
  }
}

/**
 * @fn main
 * @brief
 * main method added so that code can be compiled using native environment with library ArduinoFake
 */
int main() {
  setup();
  while(1) {
    loop();
  }
  return 0;
}