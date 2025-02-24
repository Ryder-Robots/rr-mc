#ifndef MSP_STATUS_HPP
#define MSP_STATUS_HPP

#include <stdint.h>

namespace rrobot {

    

    class MspStatus {

        public:
        void set_cycletime(uint16_t cycletime) {
            _cycletime = cycletime;
        }
        uint16_t get_cycletime() {
            return _cycletime;
        }

        void set_i2c_errors_count(uint16_t i2c_errors_count) {
            _i2c_errors_count = i2c_errors_count;
        }
        uint16_t get_i2c_errors_count() {
            return _i2c_errors_count;
        }

        void set_sensor(uint16_t sensor) {
            _sensor = sensor;
        }
        uint16_t get_sensor() {
            return _sensor;
        }

        void set_flag(uint16_t flag) {
            _flag = flag;
        }
        uint16_t get_flag() {
            return _flag;
        }

        void set_current_set(uint16_t current_set) {
            _current_set = current_set;
        }
        uint16_t get_current_set() {
            return _current_set;
        }

        private:
        uint16_t _cycletime;
        uint16_t _i2c_errors_count;
        uint16_t _sensor;
        uint32_t _flag;
        uint8_t  _current_set;
    };
}


#endif