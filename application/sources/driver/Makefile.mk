include sources/driver/Adafruit_ssd1306syp/Makefile.mk
include sources/driver/button/Makefile.mk
ifeq ($(USE_EEPROM_OPTION),USE_EEPROM)
include sources/driver/eeprom/Makefile.mk
endif
include sources/driver/flash/Makefile.mk
include sources/driver/led/Makefile.mk
include sources/driver/AsyncDelay/Makefile.mk
include sources/driver/gpio/Makefile.mk
include sources/driver/buzzer/Makefile.mk
