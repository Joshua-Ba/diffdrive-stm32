#include "kinematics.hpp"

namespace core {
WheelSpeeds inverse_kinematics(float v, float omega, float wheel_base) {
    float half = omega * wheel_base / 2.0f;
    return {v-half, v+half};
}
}
