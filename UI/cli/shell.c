/* ============================================
 * FOX.M OS - CLI Shell Implementation
 * ============================================ */

#include "shell.h"
#include "FreeRTOS.h"
#include "task.h"

/* UART0 mps2-an385 */
#define UART0_BASE  0x40004000
#define UART0_DATA  (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_STATE (*((volatile uint32_t *)(UART0_BASE + 0x04)))
#define UART0_CTRL  (*((volatile uint32_t *)(UART0_BASE + 0x08)))
#define UART0_RX    (*((volatile uint32_t *)(UART0_BASE + 0x00)))
#define UART0_RXST  (*((volatile uint32_t *)(UART0_BASE + 0x04)))

static void uart_putc(char c) { while (UART0_STATE & 0x1); UART0_DATA = c; }

/* Command registry */
static ShellCommand_t cmd_table[SHELL_MAX_CMDS];
static uint8_t cmd_count = 0;

/* Input buffer */
static char input_buf[SHELL_MAX_CMD_LEN];
static uint8_t input_len = 0;

/* ---- Built-in command handlers ---- */
static void cmd_help(int argc, char **argv)
{
    Shell_Print("\r\n=== FOX.M OS Commands ===\r\n");
    for (int i = 0; i < cmd_count; i++)
    {
        Shell_Print("  ");
        Shell_Print(cmd_table[i].name);
        Shell_Print(" - ");
        Shell_Print(cmd_table[i].description);
        Shell_Print("\r\n");
    }
    Shell_Print("=========================\r\n");
}

static void cmd_version(int argc, char **argv)
{
    Shell_Print("\r\nFOX.M OS v0.1\r\n");
    Shell_Print("Target : STM32F4 (Cortex-M4)\r\n");
    Shell_Print("Kernel : FreeRTOS\r\n");
    Shell_Print("Dev    : ToBeFox.Dev\r\n");
}

static void cmd_status(int argc, char **argv)
{
    Shell_Print("\r\n=== System Status ===\r\n");
    Shell_Print("  OS     : FOX.M OS v0.1\r\n");
    Shell_Print("  Kernel : FreeRTOS - Running\r\n");
    Shell_Print("  IR     : Ready\r\n");
    Shell_Print("  BT     : Ready\r\n");
    Shell_Print("  WiFi   : Ready\r\n");
    Shell_Print("  Power  : OK\r\n");
    Shell_Print("=====================\r\n");
}

static void cmd_ir(int argc, char **argv)
{
    Shell_Print("\r\n[IR] Sending test NEC signal...\r\n");
    Shell_Print("[IR] addr=0x01 cmd=0x45\r\n");
    Shell_Print("[IR] Done!\r\n");
}

static void cmd_clear(int argc, char **argv)
{
    Shell_Print("\033[2J\033[H"); /* ANSI clear screen */
}

/* ---- Shell API ---- */
void Shell_Init(void)
{
    cmd_count = 0;
    input_len = 0;

    /* Register built-in commands */
    Shell_RegisterCommand("help",    "Show all commands",     cmd_help);
    Shell_RegisterCommand("version", "Show OS version",       cmd_version);
    Shell_RegisterCommand("status",  "Show system status",    cmd_status);
    Shell_RegisterCommand("ir",      "Send IR test signal",   cmd_ir);
    Shell_RegisterCommand("clear",   "Clear screen",          cmd_clear);
}

void Shell_RegisterCommand(const char *name, const char *desc, cmd_handler_t handler)
{
    if (cmd_count >= SHELL_MAX_CMDS) return;
    cmd_table[cmd_count].name        = name;
    cmd_table[cmd_count].description = desc;
    cmd_table[cmd_count].handler     = handler;
    cmd_count++;
}

void Shell_Print(const char *msg)
{
    while (*msg) uart_putc(*msg++);
}

void Shell_Execute(const char *input)
{
    /* Parse command name */
    char cmd_name[32] = {0};
    int i = 0;
    while (input[i] && input[i] != ' ' && i < 31)
    {
        cmd_name[i] = input[i];
        i++;
    }

    /* Find and execute command */
    for (int j = 0; j < cmd_count; j++)
    {
        if (str_equal(cmd_name, cmd_table[j].name))
        {
            cmd_table[j].handler(0, 0);
            return;
        }
    }

    Shell_Print("[ERR] Unknown command: ");
    Shell_Print(cmd_name);
    Shell_Print("\r\nType 'help' for available commands.\r\n");
}

/* Simple string compare (no stdlib) */
int str_equal(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (*a != *b) return 0;
        a++; b++;
    }
    return *a == *b;
}

void Shell_Run(void)
{
    Shell_Print("\r\nFOX.M OS CLI Ready. Type 'help' for commands.\r\n");
    Shell_Print("fox.m> \r\n");

    /* Demo: simulate user input */
    vTaskDelay(pdMS_TO_TICKS(200));
    Shell_Print("help\r\n");
    Shell_Execute("help");

    vTaskDelay(pdMS_TO_TICKS(200));
    Shell_Print("fox.m> version\r\n");
    Shell_Execute("version");

    vTaskDelay(pdMS_TO_TICKS(200));
    Shell_Print("fox.m> status\r\n");
    Shell_Execute("status");

    vTaskDelay(pdMS_TO_TICKS(200));
    Shell_Print("fox.m> ir\r\n");
    Shell_Execute("ir");

    Shell_Print("\r\nfox.m> ");

    for (;;) vTaskDelay(pdMS_TO_TICKS(1000));
}