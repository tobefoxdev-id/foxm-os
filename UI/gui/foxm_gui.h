#ifndef FOXM_GUI_H
#define FOXM_GUI_H

/* ============================================
 * FOX.M OS - GUI Module
 * Based on LVGL + SDL2 (Linux simulation)
 * ============================================ */

void GUI_Init(void);
void GUI_Run(void);
void GUI_UpdateStatus(const char *status);

#endif /* FOXM_GUI_H */