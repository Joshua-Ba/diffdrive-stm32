#include "pid.hpp"
#include <algorithm>

float core::PID::update(float set_point, float measured, float dt){

    float error = set_point - measured;
    float p = kp*error;
    float i = 0.0;
    float d = 0.0;
    float new_integral = 0.0;
    float u = 0.0;

    if(dt != 0.0){

        new_integral = error * dt;
        integral += new_integral;
        i = ki*integral;
        d = kd*((error-last_error)/dt);
    }

    last_error = error;
    u = p+i+d;

    if (u > out_max ){
        integral -= new_integral;
        u = out_max;
    }else if(u < -out_max){
        integral -= new_integral;
        u = -out_max;
    }
    return u;
}
