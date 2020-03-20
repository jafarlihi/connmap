#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#define RCFILE "/.connmap/connmaprc"

typedef struct Config {
    uint32_t location_x;
    uint32_t location_y;
    bool white;
    bool small;
    uint32_t update_interval;
} Config;

Config *readConfig();

#endif

