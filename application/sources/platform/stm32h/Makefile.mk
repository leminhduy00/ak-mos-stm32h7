LDFILE = sources/platform/stm32h/ak.ld

CFLAGS += -I./sources/platform/stm32h

CPPFLAGS += -I./sources/platform/stm32h

VPATH += sources/platform/stm32h

# C source files
SOURCES += $(wildcard sources/platform/stm32h/*.c)
# C++ source files
SOURCES_CPP += sources/platform/stm32h/mini_cpp.cpp

# ASM source files
SOURCES_ASM += sources/platform/stm32h/sys_ctrl.s
