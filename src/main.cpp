#include <Arduino.h>
#include "multiwii.hpp"

// On PI need to disable bluetooth,  add that to the documentation

void setup()
{
  Serial.begin(9600);
  
  // Initilize pins and send back armed response.
}

void loop()
{
  Serial.println("Hello from Arduino Nano 33 BLE!");
  delay(1000);
}