#include <stdint.h>

extern uint32_t _sdata, _edata, _sidata;
extern uint32_t _sbss, _ebss;

extern uint32_t _estack;

extern int main(void);

void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dst = &_sdata;
    while(dst < &_edata){
        *dst++ = *src++;
    }

    dst = &_sbss;
    while(dst < &_ebss){
        *dst++ = 0;
    }

    main();

    while(1){}
}


typedef void (*vector_entry_t)(void);

__attribute__((section(".isr_vector")))
const vector_entry_t vector_table[] = {
    (vector_entry_t)&_estack,
    Reset_Handler,
};
