#include "complementary_filter.hpp"


float core::ComplementaryFilter::update(float omega_gyro, float theta_odom, float dt){
    float odom_theta = (1 - alpha) * theta_odom;
    float gyro_theta = alpha * (theta + omega_gyro * dt);
    theta = odom_theta + gyro_theta;
    return theta;
}
