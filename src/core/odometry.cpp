#include "odometry.hpp"
#include <cmath>


void core::Odometrie::update_position(float d_left, float d_right){
    position = core::calculate_new_position(position, wheel_base, d_left, d_right);
}

core::pose core::Odometrie::get_pose() const{
    return position;
}

core::pose core::calculate_new_position(core::pose old_position, float wheel_base, float d_left, float d_right){
    float d_s = (d_right + d_left) / 2;
    float d_t = (d_right - d_left) / wheel_base;
    float new_x = old_position.pos_x + d_s * std::cos(old_position.theta);
    float new_y = old_position.pos_y + d_s * std::sin(old_position.theta);
    float new_theta = old_position.theta + d_t;
    return core::pose{new_x, new_y, new_theta};
}
