#ifndef PLUGIN_API_H
#define PLUGIN_API_H

/* ============================================
 * FOX.M OS - Plugin API
 * ============================================ */

#include <stdint.h>

/* Plugin metadata struct */
typedef struct {
    const char *name;
    const char *version;
    const char *author;
    void (*init)(void);
    void (*run)(void);
    void (*stop)(void);
} FoxPlugin_t;

/* Plugin API functions */
void PluginLoader_Init(void);
uint8_t PluginLoader_Load(const char *plugin_name);
void PluginLoader_Unload(uint8_t plugin_id);
void PluginLoader_ListAll(void);

#endif /* PLUGIN_API_H */