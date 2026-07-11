#pragma once


namespace core{

class PID{
public:
    PID(float kp, float ki, float kd, float out_max) : kp(kp), ki(ki), kd(kd), out_max(out_max), integral(0.0), last_error(0.0){}
    float update(float set_point, float measured, float dt);

private:
    float kp;
    float ki;
    float kd;
    float out_max;
    float integral;
    float last_error;
};
}
