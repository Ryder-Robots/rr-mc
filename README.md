# rr-mc

This program is designed for the Arduino Nano 33 BLE microprocessor to execute MSP (MultiWii Serial Protocol) commands for I2C DFRobot SEN0304 ultrasonic sensors, and dual H-Bridge engines to drive Mecanum Wheels capable of omnidirectional movement. 

## Overview

The program allows the Arduino Nano 33 BLE to communicate with ultrasonic sensors using the MSP protocol. It can send commands to the sensors and process the received data.

## Hardware Requirements

- Arduino Nano 33 BLE
- Ultrasonic sensor(s)  I2C DFRobot SEN0304

## Software Requirements

- Arduino IDE
- Arduino Nano 33 BLE board support package
- ArduinoBLE library

## Installation

1. Install Visual Studio and Platoform IO plugin (see https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide).
2. Add the Arduino Nano 33 BLE board support package to your Arduino IDE.
3. Install the ArduinoBLE library through the Arduino Library Manager.

## Program Structure

The program consists of the following main components:

1. MSP packet handling functions
2. Ultrasonic sensor communication functions
3. BLE communication setup
4. Main loop for processing commands and sensor data

## Key Functions

### MSP Packet Handling

```cpp
rrobot::msp::MspStatus msp = rrobot::msp::MspStatus();

```