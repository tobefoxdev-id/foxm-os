#ifndef SHELL_H
#define SHELL_H

void Shell_Init(void);
void Shell_Run(void);
void Shell_Execute(const char *command);
void Shell_Print(const char *message);

#endif