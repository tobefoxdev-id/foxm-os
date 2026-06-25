/* ============================================
 * FOX.M OS - Startup File
 * Cortex-M3 Vector Table & Reset Handler
 * ============================================ */

#include <stdint.h>

/* Stack */
#define STACK_SIZE 8192
static uint32_t stack[STACK_SIZE] __attribute__((aligned(8)));

/* Forward declarations */
extern int main(void);
void Reset_Handler(void);
void Default_Handler(void);

/* FreeRTOS handlers - defined in port.c */
extern void xPortPendSVHandler(void);
extern void xPortSysTickHandler(void);
extern void vPortSVCHandler(void);

/* Fault Handlers */
void NMI_Handler(void)          __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void)    __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void)     __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void)   __attribute__((weak, alias("Default_Handler")));

/* Vector Table */
__attribute__((section(".vectors")))
void (*const vector_table[])(void) = {
    (void (*)(void))((uint32_t)stack + sizeof(stack)), /* Initial SP */
    Reset_Handler,          /* Reset */
    NMI_Handler,            /* NMI */
    HardFault_Handler,      /* HardFault */
    MemManage_Handler,      /* MemManage */
    BusFault_Handler,       /* BusFault */
    UsageFault_Handler,     /* UsageFault */
    0, 0, 0, 0,             /* Reserved */
    vPortSVCHandler,        /* SVC - FreeRTOS */
    0, 0,                   /* Reserved */
    xPortPendSVHandler,     /* PendSV - FreeRTOS */
    xPortSysTickHandler,    /* SysTick - FreeRTOS */
};

/* Reset Handler */
void Reset_Handler(void)
{
    main();
    while (1);
}

/* Default Handler */
void Default_Handler(void)
{
    while (1);
}