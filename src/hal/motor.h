#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "pwm.h"

typedef enum { MOTOR_LEFT, MOTOR_RIGHT } motor_side_t;

void motor_set(motor_side_t motor, float value);
void motor_brake(motor_side_t motor);


#ifdef __cplusplus
}
#endif
