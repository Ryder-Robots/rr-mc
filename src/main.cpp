#include <Arduino.h>
#include <multiwii.hpp>

/**
 * 
 * $M[direction][size][command][data][checksum]
 */

// put function declarations here:
void setup() {
  // Initilize pins and send back armed response.
  Serial.println("test");
}

void loop() {
  Serial.println("test");
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