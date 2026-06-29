/* ============================================
 * FOX.M OS - GUI Implementation
 * LVGL + SDL2 Linux Simulation
 * ============================================ */

#include "lvgl/lvgl.h"
#include "sdl/sdl.h"
#include "foxm_gui.h"
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

void GUI_Init(void)
{
    lv_init();
    sdl_init();

    /* Setup display buffer */
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, 480 * 10);

    /* Register display driver */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res  = 480;
    disp_drv.ver_res  = 320;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    /* Register input driver */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type    = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);
}

void GUI_Run(void)
{
    /* Main screen */
    screen_main = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_main, lv_color_hex(0x1a1a2e), 0);
    lv_scr_load(screen_main);

    /* Top panel */
    panel_top = lv_obj_create(screen_main);
    lv_obj_set_size(panel_top, 480, 50);
    lv_obj_align(panel_top, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(panel_top, lv_color_hex(0x16213e), 0);
    lv_obj_set_style_border_width(panel_top, 0, 0);
    lv_obj_set_style_radius(panel_top, 0, 0);

    /* Title */
    label_title = lv_label_create(panel_top);
    lv_label_set_text(label_title, "FOX.M OS v0.1");
    lv_obj_set_style_text_color(label_title, lv_color_hex(0xFF6B35), 0);
    lv_obj_align(label_title, LV_ALIGN_CENTER, 0, 0);

    /* Status panel */
    panel_status = lv_obj_create(screen_main);
    lv_obj_set_size(panel_status, 440, 220);
    lv_obj_align(panel_status, LV_ALIGN_CENTER, 0, 20);
    lv_obj_set_style_bg_color(panel_status, lv_color_hex(0x0f3460), 0);
    lv_obj_set_style_border_color(panel_status, lv_color_hex(0xFF6B35), 0);
    lv_obj_set_style_border_width(panel_status, 1, 0);
    lv_obj_set_style_radius(panel_status, 8, 0);

    /* Status labels */
    label_status = lv_label_create(panel_status);
    lv_label_set_text(label_status, "System Status");
    lv_obj_set_style_text_color(label_status, lv_color_hex(0xFFFFFF), 0);
    lv_obj_align(label_status, LV_ALIGN_TOP_MID, 0, 10);

    label_ir = lv_label_create(panel_status);
    lv_label_set_text(label_ir, "IR Driver    : Ready");
    lv_obj_set_style_text_color(label_ir, lv_color_hex(0x00FF88), 0);
    lv_obj_align(label_ir, LV_ALIGN_TOP_LEFT, 20, 50);

    label_bt = lv_label_create(panel_status);
    lv_label_set_text(label_bt, "Bluetooth    : Ready");
    lv_obj_set_style_text_color(label_bt, lv_color_hex(0x00FF88), 0);
    lv_obj_align(label_bt, LV_ALIGN_TOP_LEFT, 20, 80);

    label_power = lv_label_create(panel_status);
    lv_label_set_text(label_power, "Power        : OK");
    lv_obj_set_style_text_color(label_power, lv_color_hex(0x00FF88), 0);
    lv_obj_align(label_power, LV_ALIGN_TOP_LEFT, 20, 110);

    /* Main loop */
    while (1)
    {
        lv_timer_handler();
        usleep(5000);
    }
}

void GUI_UpdateStatus(const char *status)
{
    if (label_status)
        lv_label_set_text(label_status, status);
}