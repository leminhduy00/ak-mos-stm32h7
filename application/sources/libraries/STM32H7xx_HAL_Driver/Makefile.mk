CFLAGS += -I./sources/libraries/STM32H7xx_HAL_Driver/Inc
CPPFLAGS += -I./sources/libraries/STM32H7xx_HAL_Driver/Inc

VPATH += sources/libraries/STM32H7xx_HAL_Driver/Src

# C source files
SOURCES += $(wildcard sources/libraries/STM32H7xx_HAL_Driver/Src/*.c)