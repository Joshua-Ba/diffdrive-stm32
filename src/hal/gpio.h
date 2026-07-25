#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>


typedef enum {
    INPUT = 0,
    GENERAL_OUT = 1,
    ALTERNATE_FUNC = 2,
    ANALOG = 3
} PortMode;

typedef struct {
    uint32_t port;
    uint32_t pin;
}gpio_pin_t;

void gpio_set(gpio_pin_t pin, uint8_t value);

void gpio_setup_mode(gpio_pin_t pin, PortMode mode);

void gpio_toggle(gpio_pin_t pin);

void gpio_set_alternate_function(gpio_pin_t pin, uint8_t af);

#ifdef __cplusplus
}
#endif
