/* ============================================
 * FOX.M OS - GUI Implementation
 * LVGL + SDL2 Linux Simulation
 * ============================================ */

#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "foxm_gui.h"
#include <SDL2/SDL.h>
#include <unistd.h>

/* Display buffer */
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf1[480 * 10];

/* UI elements */
static lv_obj_t *screen_main;
static lv_obj_t *label_title;
static lv_obj_t *label_status;
static lv_obj_t *label_ir;
static lv_obj_t *label_bt;
static lv_obj_t *label_power;
static lv_obj_t *panel_top;
static lv_obj_t *panel_status;

static void ticker_thread(void *data)
{
    (void)data;
    while (1)
    {
        SDL_Delay(5);
        lv_tick_inc(5);
    }
}

void GUI_Init(void)
{
    lv_init();

    /* Init SDL2 display driver */
    monitor_init();
    mouse_init();

    /* Setup display buffer */
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 480 * 10);

    /* Register display driver */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res  = 480;
    disp_drv.ver_res  = 320;