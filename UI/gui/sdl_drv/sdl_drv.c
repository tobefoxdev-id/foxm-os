/* ============================================
 * FOX.M OS - Custom SDL2 Driver for LVGL v9
 * ============================================ */

#include "sdl_drv.h"

static SDL_Window   *window   = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture  *texture  = NULL;

static int mouse_x = 0;
static int mouse_y = 0;
static int mouse_pressed = 0;
static int quit_flag = 0;

void sdl_drv_init(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "FOX.M OS v0.1 - GUI Simulation",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SDL_HOR_RES, SDL_VER_RES,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        SDL_HOR_RES, SDL_VER_RES
    );
}

void sdl_drv_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_p)
{
    /* Process SDL events */
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) quit_flag = 1;
        if (e.type == SDL_MOUSEMOTION)
        {
            mouse_x = e.motion.x;
            mouse_y = e.motion.y;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) mouse_pressed = 1;
        if (e.type == SDL_MOUSEBUTTONUP)   mouse_pressed = 0;
    }

    /* Update texture */
    int32_t w = area->x2 - area->x1 + 1;
    int32_t h = area->y2 - area->y1 + 1;

    SDL_Rect rect = {
        .x = area->x1,
        .y = area->y1,
        .w = w,
        .h = h
    };

    SDL_UpdateTexture(texture, &rect, color_p, w * sizeof(lv_color_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    lv_disp_flush_ready(drv);
}

void sdl_drv_mouse_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    data->point.x = mouse_x;
    data->point.y = mouse_y;
    data->state   = mouse_pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

int sdl_drv_quit_requested(void)
{
    return quit_flag;
}