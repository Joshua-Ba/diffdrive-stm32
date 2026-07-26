#include <stdint.h>
#include "gpio.h"
#include "motor.h"

int main(void)
{

    gpio_pin_t led = {
        .port = 0x40020800u,
        .pin = 13
    };   // Port C, Pin 13 (LED Blau)
    gpio_setup_mode(led, GENERAL_OUT);

    tim2_pwm_init();
    motor_set(MOTOR_LEFT, 0.8f);
    motor_set(MOTOR_RIGHT, 0.8f);

    while (1) {
        gpio_toggle(led);
        for (volatile int i = 0; i < 500000; i++);
    }
}
