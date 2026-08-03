#include "encoder.h"

#define RCC_APB1ENR (*(volatile uint32_t *)(0x40023840u))
#define TIMx_CCMR1 0x18u
#define TIMx_SMCR 0x08
#define TIMx_ARR 0x2cu
#define TIMx_CR1 0x00u
#define TIMx_CCER 0x20u
#define TIM3 0x40000400u
#define TIM4 0x40000800u
#define TIM_REG(base, offset) (*(volatile uint32_t*)((base) + (offset)))


typedef struct {
    uint32_t timer_base;
    uint32_t rcc_bit;
    gpio_pin_t ch1_pin;
    gpio_pin_t ch2_pin;
} encoder_config_t;



static void setup_encoder(encoder_config_t encoder){
    RCC_APB1ENR |= (1 << encoder.rcc_bit);

    TIM_REG(encoder.timer_base, TIMx_CCER) = 0;
    TIM_REG(encoder.timer_base, TIMx_CCMR1) = 0;
    TIM_REG(encoder.timer_base, TIMx_CCMR1) &= ~(0b11 << 0);
    TIM_REG(encoder.timer_base, TIMx_CCMR1) |= (0b01 << 0);

    TIM_REG(encoder.timer_base, TIMx_CCMR1) &= ~(0b11 << 8);
    TIM_REG(encoder.timer_base, TIMx_CCMR1) |= (0b01 << 8);

    TIM_REG(encoder.timer_base, TIMx_CCER) |= (0b1 << 0);
    TIM_REG(encoder.timer_base, TIMx_CCER) |= (0b1 << 4);

    TIM_REG(encoder.timer_base, TIMx_SMCR) &= ~(0b111 << 0);
    TIM_REG(encoder.timer_base, TIMx_SMCR) |= (0b011 << 0);

    TIM_REG(encoder.timer_base, TIMx_ARR) = 0xFFFF;

    gpio_setup_mode(encoder.ch1_pin, ALTERNATE_FUNC);
    gpio_set_alternate_function(encoder.ch1_pin, 2);
    gpio_set_pull(encoder.ch1_pin, PULL_UP);

    gpio_setup_mode(encoder.ch2_pin, ALTERNATE_FUNC);
    gpio_set_alternate_function(encoder.ch2_pin, 2);
    gpio_set_pull(encoder.ch2_pin, PULL_UP);

    TIM_REG(encoder.timer_base, TIMx_CR1) |= (1 << 0);

}


void timx_encoder_init(){

    gpio_pin_t pb4 = {
        .port = 0x40020400u,
        .pin = 4
    };
    gpio_pin_t pb5 = {
        .port = 0x40020400u,
        .pin = 5
    };
    gpio_pin_t pb6 = {
        .port = 0x40020400u,
        .pin = 6
    };
    gpio_pin_t pb7 = {
        .port = 0x40020400u,
        .pin = 7
    };
    encoder_config_t left  = { .timer_base = TIM3, .rcc_bit = 1, .ch1_pin = pb4, .ch2_pin = pb5 };
    encoder_config_t right = { .timer_base = TIM4, .rcc_bit = 2, .ch1_pin = pb6, .ch2_pin = pb7 };
    setup_encoder(left);
    setup_encoder(right);
}
