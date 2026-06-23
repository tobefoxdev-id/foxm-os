# ============================================
# FOX.M OS - Makefile
# Target: STM32F4 (Cortex-M4)
# ============================================

# Toolchain
CC      = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
SIZE    = arm-none-eabi-size

# Project Name
TARGET = foxm-os

# CPU Flags (STM32F4 = Cortex-M4 with FPU)
CPU_FLAGS = -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard

# Compiler Flags
CFLAGS  = $(CPU_FLAGS) -O0 -g -Wall
CFLAGS += -DSTM32F4

# Include Paths
INCLUDES  = -ICore
INCLUDES += -ICore/Kernel
INCLUDES += -IDrivers/ir
INCLUDES += -IUI/cli
INCLUDES += -IPlugins
INCLUDES += -IConfig

# Source Files
SRCS  = Core/main.c
SRCS += Core/Kernel/app_manager.c
SRCS += Core/Kernel/event_system.c
SRCS += Core/Kernel/power_manager.c
SRCS += Drivers/ir/ir_tx.c
SRCS += Drivers/ir/ir_rx.c
SRCS += UI/cli/shell.c
SRCS += Plugins/plugin_loader.c

# Object Files
OBJS = $(SRCS:.c=.o)

# Build
all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CC) $(CPU_FLAGS) $(OBJS) -o $@
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET).elf

.PHONY: all clean