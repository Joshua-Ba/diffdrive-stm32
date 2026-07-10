#pragma once

namespace core {
struct pose {
    float pos_x;
    float pos_y;
    float theta;
};

class Odometrie{
public:
    Odometrie(float wheel_base) : wheel_base(wheel_base), position{0.0f, 0.0f, 0.0f}{}
    void update_position(float d_left, float d_right);
    pose get_pose() const;
private:
    float wheel_base;
    pose position;
};

pose calculate_new_position(pose old_position, float wheel_base, float d_left, float d_right);
}
