#pragma once

namespace core {

struct WheelSpeeds {
    float left;
    float right;
};

WheelSpeeds inverse_kinematics(float v, float omega, float wheel_base);
}
