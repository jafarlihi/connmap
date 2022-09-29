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
CFLAGS:=-std=gnu11 -I$(INCLUDES) $(shell pkg-config --libs --cflags cairo x11 xfixes) -lm

CFILES:=$(shell find $(SOURCES) -printf '%P ' -name '*.c')
OFILES:=$(patsubst %.c,$(BUILD)/%.o,$(CFILES))

.PHONY: install build debug clean mkdir
.DEFAULT_GOAL:=build

install: build
	cd ./connmap/resources && unzip -n ipv4.csv.zip
	cp -R ./connmap ~/.config/
	mkdir -p ~/.local/bin
	cp connmap.elf ~/.local/bin/connmap

build: CFLAGS+=-O0
build: mkdir $(OFILES)
	$(CC) $(OFILES) -o $(TARGET).elf $(CFLAGS)

debug: CFLAGS+=-O0 -ggdb -D DEBUG
debug: mkdir $(OFILES)
	$(CC) $(OFILES) -o $(TARGET).debug.elf $(CFLAGS)

mkdir:
	mkdir -p $(BUILD)

clean:
	-rm -rf $(BUILD)
	-rm -f $(TARGET).elf
	-rm -f $(TARGET).debug.elf
	-rm -f ./connmap/resources/ipv4.csv

$(OFILES): $(BUILD)/%.o: $(SOURCES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
