#include "gpio.h"


#define AHB1ENR_OFFSET ((uintptr_t)0x30u)
#define MODER_Offset ((uintptr_t)0x00u)
#define ODR_Offset ((uintptr_t)0x14u)
#define RCC_AHB1ENR (*(volatile uint32_t *)(0x40023800u + 0x30u))
#define GPIO_REG(base, offset) (*(volatile uint32_t*)((base) + (offset)))
#define GPIO_PUPDR 0x0Cu


void gpio_set(gpio_pin_t pin, uint8_t value){
    if(value){
        GPIO_REG(pin.port, ODR_Offset) |= (1 << pin.pin);
    }else{
        GPIO_REG(pin.port, ODR_Offset) &= ~(1 << pin.pin);
    }
}

void gpio_toggle(gpio_pin_t pin){
    GPIO_REG(pin.port, ODR_Offset) ^= (1 << pin.pin);
}

void gpio_setup_mode(gpio_pin_t pin, PortMode mode){
    uint32_t rel = pin.port - 0x40020000u;
    uint8_t clock = rel / 0x400u;
    RCC_AHB1ENR |= (1 << clock);
    GPIO_REG(pin.port, MODER_Offset) &= ~(0b11 << pin.pin * 2);
    GPIO_REG(pin.port, MODER_Offset) |= (mode << pin.pin * 2);

}


void gpio_set_alternate_function(gpio_pin_t pin, uint8_t af){
    uint32_t offset = 0x20 + (pin.pin/8)*4;
    uint32_t position = (pin.pin % 8) * 4;

    GPIO_REG(pin.port, offset) &= ~(0b1111 << position);
    GPIO_REG(pin.port, offset) |= (af << position);
}

void gpio_set_pull(gpio_pin_t pin, gpio_pull_t pull){
    GPIO_REG(pin.port, GPIO_PUPDR) &= ~(0b11 << (2 * pin.pin));
    GPIO_REG(pin.port, GPIO_PUPDR) |= (pull << (2 * pin.pin));
}
