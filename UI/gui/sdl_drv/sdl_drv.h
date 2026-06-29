#ifndef SDL_DRV_H
#define SDL_DRV_H

#include "lvgl/lvgl.h"
#include <SDL2/SDL.h>

#define SDL_HOR_RES 480
#define SDL_VER_RES 320

void sdl_drv_init(void);
void sdl_drv_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p);
void sdl_drv_mouse_read(lv_indev_drv_t *drv, lv_indev_data_t *data);
int sdl_drv_quit_requested(void);

#endif /* SDL_DRV_H */