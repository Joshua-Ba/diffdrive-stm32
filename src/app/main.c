#include <stdint.h>
#include "gpio.h"
#include "pwm.h"

int main(void)
{

    gpio_pin_t led = {
        .port = 0x40020800u,
        .pin = 13
    };   // Port C, Pin 13 (LED Blau)
    gpio_setup_mode(led, GENERAL_OUT);

    tim2_pwm_init();
    pwm_set_duty(0.25f, MOTOR_LEFT);
    pwm_set_duty(0.75f, MOTOR_RIGHT);

    while (1) {
        gpio_toggle(led);
        for (volatile int i = 0; i < 500000; i++);
    }
}
