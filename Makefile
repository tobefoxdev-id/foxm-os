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
CPU_FLAGS = -mcpu=cortex-m3 -mthumb

# Compiler Flags
CFLAGS  = $(CPU_FLAGS) -O0 -g -Wall
CFLAGS += -DSTM32F4

# FreeRTOS Path
FREERTOS = Core/FreeRTOS

# Include Paths
INCLUDES  = -ICore
INCLUDES += -ICore/Kernel
INCLUDES += -I$(FREERTOS)/include
INCLUDES += -I$(FREERTOS)/portable/GCC/ARM_CM3
INCLUDES += -IDrivers/ir
INCLUDES += -IUI/cli
INCLUDES += -IPlugins
INCLUDES += -IConfig
INCLUDES += -IApps/ir_app
INCLUDES += -IApps/bt_app

# FreeRTOS Source Files
FREERTOS_SRCS  = $(FREERTOS)/tasks.c
FREERTOS_SRCS += $(FREERTOS)/queue.c
FREERTOS_SRCS += $(FREERTOS)/list.c
FREERTOS_SRCS += $(FREERTOS)/timers.c
FREERTOS_SRCS += $(FREERTOS)/event_groups.c
FREERTOS_SRCS += $(FREERTOS)/portable/GCC/ARM_CM3/port.c
FREERTOS_SRCS += $(FREERTOS)/portable/MemMang/heap_4.c

# Project Source Files
SRCS  = Core/startup.c
SRCS += Core/main.c
SRCS += Core/Kernel/app_manager.c
SRCS += Core/Kernel/event_system.c
SRCS += Core/Kernel/power_manager.c
SRCS += Drivers/ir/ir_tx.c
SRCS += Drivers/ir/ir_rx.c
SRCS += UI/cli/shell.c
SRCS += Plugins/plugin_loader.c
#SRCS += Core/freertos_hooks.c
SRCS += Apps/ir_app/ir_scanner.c
SRCS += Apps/bt_app/bt_scanner.c


# All Sources
ALL_SRCS = $(SRCS) $(FREERTOS_SRCS)

# Object Files
OBJS = $(ALL_SRCS:.c=.o)

# Build
all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CC) $(CPU_FLAGS) $(OBJS) --specs=nano.specs --specs=nosys.specs -T Core/linker.ld -o $@
	$(SIZE) $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET).elf

.PHONY: all clean