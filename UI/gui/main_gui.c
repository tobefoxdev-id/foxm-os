/* ============================================
 * FOX.M OS - GUI Entry Point
 * Linux Simulation via SDL2
 * ============================================ */

#include "foxm_gui.h"
#include <stdio.h>

int main(void)
{
    printf("==========================================\n");
    printf("  FOX.M OS v0.1 - GUI Simulation\n");
    printf("  Powered by LVGL + SDL2\n");
    printf("==========================================\n");

    GUI_Init();
    GUI_Run();

    return 0;
}