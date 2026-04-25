include sources/driver/gpio/Makefile.mk
include sources/driver/iwdg/Makefile.mk
include sources/driver/usart/Makefile.mk
include sources/driver/timer/Makefile.mk
include sources/driver/spi/Makefile.mk
include sources/driver/flash/Makefile.mk

CFLAGS   += -I./sources/driver/led

CPPFLAGS += -I./sources/driver/led

VPATH += sources/driver/led

SOURCES += sources/driver/led/led.c
