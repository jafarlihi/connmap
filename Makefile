TARGET:=connmap

SOURCES:=./sources
INCLUDES:=./includes

ifeq ($(MAKECMDGOALS),build)
	BUILD:=./build
else ifeq ($(MAKECMDGOALS),debug)
	BUILD:=./build/debug
else
	BUILD:=./build
endif

CC:=gcc
CFLAGS:=-std=gnu11 -I$(INCLUDES) $(shell pkg-config --libs --cflags cairo x11)

CFILES:=$(shell find $(SOURCES) -printf '%P ' -name '*.c')
OFILES:=$(patsubst %.c,$(BUILD)/%.o,$(CFILES))

.PHONY: install build debug clean mkdir
.DEFAULT_GOAL:=build

install: build
	cp -R ./connmap ~/.config/

build: CFLAGS+=-O0
build: mkdir $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(TARGET).exe

debug: CFLAGS+=-O0 -ggdb -D DEBUG
debug: mkdir $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -o $(TARGET).debug.exe

mkdir:
	mkdir -p $(BUILD)

clean:
	rm -rf $(BUILD)
	rm -f $(TARGET).exe
	rm -f $(TARGET).debug.exe

$(OFILES): $(BUILD)/%.o: $(SOURCES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
