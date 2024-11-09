#ifndef RREXCEPTIONS_HPP
#define RREXCEPTIONS_HPP

/**
 * Arduino does not support standard exceptions due to memory constraints,
 * so exceptions are an int
 */
namespace rrobot {

class RrExceptions {
   public:
    static const int RR_MSP_HEADER = 500;
    static const int RR_MSP_INVALID_LEN = 501;
    static const int RR_INVALID_FIELD = 502;
    static const int RR_INVALID_CHECKSUM = 503;
};
}  // namespace rrobot

#endif  // RREXCEPTIONS_HPP