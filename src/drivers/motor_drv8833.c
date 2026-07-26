#include "motor.h"


typedef struct {
    pwm_channel_t ch_fwd;
    pwm_channel_t ch_rev;
}motor_channels_t;



static motor_channels_t convert_side_to_channels(motor_side_t motor){
    motor_channels_t channels;

    if(motor == MOTOR_LEFT){
        channels.ch_fwd = CHANNEL_1;
        channels.ch_rev = CHANNEL_2;
    }else{
        channels.ch_fwd = CHANNEL_3;
        channels.ch_rev = CHANNEL_4;
    }
    return channels;
}



void motor_set(motor_side_t motor, float value){

    motor_channels_t channels = convert_side_to_channels(motor);

    if(value >= 0.0f){
        pwm_set_duty(value, channels.ch_fwd);
        pwm_set_duty(0.0f, channels.ch_rev);

    }else{
        pwm_set_duty(-value, channels.ch_rev);
        pwm_set_duty(0.0f, channels.ch_fwd);
    }

}



void motor_brake(motor_side_t motor){
    motor_channels_t channels = convert_side_to_channels(motor);

    pwm_set_duty(1.0f, channels.ch_fwd);
    pwm_set_duty(1.0f, channels.ch_rev);

}
