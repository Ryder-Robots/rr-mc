#include <controller_msp_sensor.hpp>

using namespace rrobot;

void* MspSensorController::execute(void* command) {
    MspSensor* sensor = new MspSensor();
    float x = 0, y = 0, z = 0;

    sensor->set_accAvail(ble.accelerationAvailable());
    if (sensor->get_accAvail()) {
        ble.readAcceleration(x, y, z);
    }
    sensor->set_accX(x);
    sensor->set_accY(y);
    sensor->set_accZ(z);

    x = 0, y = 0, z = 0;
    sensor->set_gyroAvail(ble.gyroscopeAvailable());
    if (sensor->get_gyroAvail()) {
        ble.readGyroscope(x, y, z);
    }
    sensor->set_gyroX(x);
    sensor->set_gyroY(y);
    sensor->set_gyroZ(z);

    x = 0, y = 0, z = 0;
    sensor->set_gyroAvail(ble.magneticFieldAvailable());
    if (sensor->get_magAvail()) {
        ble.readMagneticField(x, y, z);
    }
    sensor->set_magX(x);
    sensor->set_magY(y);
    sensor->set_magZ(z);
}

RrEncoder* MspSensorController::encoder() {
    return _encoder;
}