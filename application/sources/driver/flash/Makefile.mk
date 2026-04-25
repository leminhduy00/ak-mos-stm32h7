CFLAGS += -I./sources/driver/flash
CPPFLAGS += -I./sources/driver/flash

VPATH += sources/driver/flash

SOURCES += sources/driver/flash/flash.c
SOURCES += sources/driver/flash/flash_internal.c
SOURCES += sources/driver/flash/w25qxx.c
