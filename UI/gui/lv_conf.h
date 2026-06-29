#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/* Color depth */
#define LV_COLOR_DEPTH 32

/* Display resolution */
#define LV_HOR_RES_MAX 480
#define LV_VER_RES_MAX 320

/* Memory */
#define LV_MEM_CUSTOM 0
#define LV_MEM_SIZE (64 * 1024U)

/* HAL */
#define LV_TICK_CUSTOM 1
#define LV_TICK_CUSTOM_INCLUDE <SDL2/SDL.h>
#define LV_TICK_CUSTOM_SYS_TIME_EXPR (SDL_GetTicks())

/* Font */
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/* Enable features */
#define LV_USE_PERF_MONITOR 0
#define LV_USE_LOG 0

#endif /* LV_CONF_H */