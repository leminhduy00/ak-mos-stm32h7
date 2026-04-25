CFLAGS += -I./sources/libraries/STM32H7xx_HAL_Driver/Inc
CPPFLAGS += -I./sources/libraries/STM32H7xx_HAL_Driver/Inc

VPATH += sources/libraries/STM32H7xx_HAL_Driver/Src

# C source files
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_gpio.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_uart_ex.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_cortex.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_exti.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_spi.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_tim_ex.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_flash_ex.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_i2c.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_pwr_ex.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_dma.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_iwdg.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_mdma.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_hsem.c
SOURCES += ./sources/libraries/STM32H7xx_HAL_Driver/Src/stm32h7xx_hal_rcc_ex.c
