LDFILE = sources/platform/stm32h/ak.ld

CFLAGS += -I./sources/platform/stm32h

CPPFLAGS += -I./sources/platform/stm32h

VPATH += sources/platform/stm32h

# C source files
SOURCES += sources/platform/stm32h/stm32h.c
SOURCES += sources/platform/stm32h/system.c
SOURCES += sources/platform/stm32h/sys_cfg.c
SOURCES += sources/platform/stm32h/io_cfg.c
SOURCES += sources/platform/stm32h/system_stm32h7xx.c
