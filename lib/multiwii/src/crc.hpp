#ifndef CRC_HPP
#define CRC_HPP

#include <Arduino.h>
#include <stdint.h>

namespace rrobot {
class Crc32 {
   private:
    static const uint32_t POLYNOMIAL = 0xEDB88320;
    uint32_t table[256];

    void generate_table() {
        for (uint32_t i = 0; i < 256; ++i) {
            uint32_t crc = i;
            for (int j = 0; j < 8; ++j) {
                crc = (crc >> 1) ^ ((crc & 1) * POLYNOMIAL);
            }
            table[i] = crc;
        }
    }

   public:
    Crc32() { generate_table(); }

    uint32_t calculate(const uint8_t* data, size_t length) {
        uint32_t crc = 0xFFFFFFFF;
        for (size_t i = 0; i < length; ++i) {
            crc = (crc >> 8) ^ table[(crc ^ data[i]) & 0xFF];
        }
        return crc ^ 0xFFFFFFFF;
    }
};
}  // namespace rrobot
#endif