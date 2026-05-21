CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -Wpedantic
CPPFLAGS ?= -Iapp -IBSP -Idriver -Imiddleware
TARGET ?= build/smart_home

SOURCES := \
	app/main.c \
	app/smart_home.c \
	BSP/bsp_console.c \
	BSP/bsp_storage.c \
	driver/device.c \
	driver/light.c \
	driver/air_conditioner.c \
	driver/security_alarm.c \
	middleware/basic_ui.c

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(SOURCES)
	@mkdir -p build
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf build
