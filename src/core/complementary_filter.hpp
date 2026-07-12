#pragma once

namespace core {

class ComplementaryFilter{
public:
    ComplementaryFilter(float alpha) : alpha(alpha), theta(0.0){};
    float update(float omega_gyro, float theta_odom, float dt);

private:
    float alpha;
    float theta;

};

}
