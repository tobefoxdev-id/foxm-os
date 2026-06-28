#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

/* ============================================
 * FOX.M OS - CLI Shell
 * ============================================ */

#define SHELL_MAX_CMD_LEN   64
#define SHELL_MAX_ARGS      8
#define SHELL_MAX_CMDS      16

/* Command handler typedef */
typedef void (*cmd_handler_t)(int argc, char **argv);

/* Command struct */
typedef struct {
    const char    *name;
    const char    *description;
    cmd_handler_t  handler;
} ShellCommand_t;

/* API */
void Shell_Init(void);
void Shell_Run(void);
void Shell_Execute(const char *input);
void Shell_Print(const char *msg);
void Shell_RegisterCommand(const char *name, const char *desc, cmd_handler_t handler);

#endif /* SHELL_H */