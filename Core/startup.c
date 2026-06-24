/* ============================================
 * FOX.M OS - Startup File
 * Cortex-M3 Vector Table & Reset Handler
 * ============================================ */

#include <stdint.h>

/* Stack size */
#define STACK_SIZE 4096
static uint32_t stack[STACK_SIZE];

/* Forward declarations */
extern int main(void);
void Reset_Handler(void);
void Default_Handler(void);

/* Weak aliases for interrupt handlers */
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void)       __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void)      __attribute__((weak, alias("Default_Handler")));

/* Vector Table */
__attribute__((section(".vectors")))
void (*const vector_table[])(void) = {
    (void (*)(void))((uint32_t)stack + sizeof(stack)), /* Initial SP */
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0, 0, 0, 0,
    SVC_Handler,
    0, 0,
    PendSV_Handler,
    SysTick_Handler,
};

/* Reset Handler */
void Reset_Handler(void)
{
    /* Call main */
    main();
    /* Loop forever if main returns */
    while (1);
}

/* Default Handler */
void Default_Handler(void)
{
    while (1);
}