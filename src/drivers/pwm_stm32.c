#include "pwm.h"

#define RCC_APB1ENR (*(volatile uint32_t *)(0x40023840u))
#define TIM2 0x40000000u

#define TIM2_REG(offset) (*(volatile uint32_t*)(TIM2 + (offset)))
#define TIM2_PSC 0x28u
#define TIM2_ARR 0x2cu
#define TIM2_CCER 0x20u
#define TIM2_CR1 0x00u

#define TIM2_CCMR1 0x18u
#define TIM2_CCR1 0x34u
#define TIM2_CCR2 0x38u

#define TIM2_CCMR2 0x1Cu
#define TIM2_CCR3 0x3Cu
#define TIM2_CCR4 0x40u


typedef struct {
    uint32_t ccmr_offset;
    uint32_t ccmr_position;
    uint32_t ccmr_preload;
    uint32_t ccer_bit;
    gpio_pin_t pin;
}pwm_channel_init_t;


static void setup_channel(pwm_channel_init_t channel){
    TIM2_REG(channel.ccmr_offset) &= ~(0b111 << channel.ccmr_position);
    TIM2_REG(channel.ccmr_offset) |= (0b110 << channel.ccmr_position);
    TIM2_REG(channel.ccmr_offset) |= (1 << channel.ccmr_preload);
    TIM2_REG(TIM2_CCER) |= (1 << channel.ccer_bit);
    gpio_setup_mode(channel.pin, ALTERNATE_FUNC);
    gpio_set_alternate_function(channel.pin, 1);
}


void tim2_pwm_init(){
    RCC_APB1ENR |= (1 << 0);
    TIM2_REG(TIM2_PSC) = 0;
    TIM2_REG(TIM2_ARR) = 799;

    gpio_pin_t pa0 = {
        .port = 0x40020000u,
        .pin = 0
    };
    pwm_channel_init_t pwm_pa0 = {
        .ccmr_offset = TIM2_CCMR1,
        .ccmr_position = 4,
        .ccmr_preload = 3,
        .ccer_bit = 0,
        .pin = pa0
    };
    setup_channel(pwm_pa0);
    TIM2_REG(TIM2_CCR1) = 0;


    gpio_pin_t pa1 = {
        .port = 0x40020000u,
        .pin = 1
    };
    pwm_channel_init_t pwm_pa1 = {
        .ccmr_offset = TIM2_CCMR1,
        .ccmr_position = 12,
        .ccmr_preload = 11,
        .ccer_bit = 4,
        .pin = pa1
    };
    setup_channel(pwm_pa1);
    TIM2_REG(TIM2_CCR2) = 0;

    gpio_pin_t pa2 = {
        .port = 0x40020000u,
        .pin = 2
    };
    pwm_channel_init_t pwm_pa2 = {
        .ccmr_offset = TIM2_CCMR2,
        .ccmr_position = 4,
        .ccmr_preload = 3,
        .ccer_bit = 8,
        .pin = pa2
    };
    setup_channel(pwm_pa2);
    TIM2_REG(TIM2_CCR3) = 0;

    gpio_pin_t pa3 = {
        .port = 0x40020000u,
        .pin = 3
    };
    pwm_channel_init_t pwm_pa3 = {
        .ccmr_offset = TIM2_CCMR2,
        .ccmr_position = 12,
        .ccmr_preload = 11,
        .ccer_bit = 12,
        .pin = pa3
    };
    setup_channel(pwm_pa3);
    TIM2_REG(TIM2_CCR4) = 0;

    TIM2_REG(TIM2_CR1) |= (1 << 0);
}


void pwm_set_duty(float duty, pwm_channel_t channel){
    float min_clamped_duty = duty < 0.0f ? 0.0f : duty;
    float clamped_duty = min_clamped_duty > 1.0f ? 1.0f : min_clamped_duty;
    uint32_t max_value = TIM2_REG(TIM2_ARR) + 1;
    uint32_t ccr_offset = TIM2_CCR1 + 4 * channel;
    TIM2_REG(ccr_offset) = max_value * clamped_duty;
}
