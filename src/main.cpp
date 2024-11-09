#include <Arduino.h>
#include <stdint.h>
#include "multiwii.hpp"


// UART mySerial1(digitalPinToPinName(4), digitalPinToPinName(3), NC, NC);

// On PI need to disable bluetooth,  add that to the documentation

void setup()
{
  // Initilize pins and send back armed response.
  Serial.begin(9600); 
}

void loop()
{

  uint8_t* arr = reinterpret_cast<uint8_t*>(malloc(5));
  arr[0] = 1;
  arr[1] = 2;
  arr[2] = 3;
  arr[3] = 4;
  arr[4] = 5;
  rrobot::MultiWii msp = rrobot::MultiWii();
  uint8_t* package = msp.serialize(rrobot::MspCommands::MSP_STATUS ,5, arr);

  // Serial1.write(package, 6 + 5);
  // Serial1.flush();
  Serial.println('a');
  delay(1000);
  free(package);
}