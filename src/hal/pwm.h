#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "gpio.h"

typedef enum { CHANNEL_1, CHANNEL_2, CHANNEL_3, CHANNEL_4 } pwm_channel_t;


void tim2_pwm_init();

void pwm_set_duty(float duty, pwm_channel_t channel);

#ifdef __cplusplus
}
#endif
