/* ============================================
 * FOX.M OS - FreeRTOS Port Hooks for QEMU
 * ============================================ */

#include "FreeRTOS.h"
#include "task.h"

/* Override SysTick config for QEMU */
void vPortSetupTimerInterrupt(void)
{
    /* QEMU mps2-an385 SysTick setup */
    #define SYSTICK_CTRL   (*((volatile uint32_t *)0xE000E010))
    #define SYSTICK_LOAD   (*((volatile uint32_t *)0xE000E014))
    #define SYSTICK_VAL    (*((volatile uint32_t *)0xE000E018))

    SYSTICK_LOAD = (25000000 / configTICK_RATE_HZ) - 1;
    SYSTICK_VAL  = 0;
    SYSTICK_CTRL = 0x07; /* Enable, interrupt, use processor clock */
}