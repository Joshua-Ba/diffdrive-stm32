#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "gpio.h"

typedef enum { MOTOR_LEFT, MOTOR_RIGHT } motor_channel_t;

void tim2_pwm_init();

void pwm_set_duty(float duty, motor_channel_t motor);

#ifdef __cplusplus
}
#endif
