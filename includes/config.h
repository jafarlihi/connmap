#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#define RCFILE "/.config/connmap/connmaprc"
#define RESOURCES "/.config/connmap/resources/"
#define IPV4FILE "/.config/connmap/resources/ipv4.csv"
#define COORDINATESFILE "/.config/connmap/resources/coordinates.csv"

typedef struct Config {
    uint32_t location_x;
    uint32_t location_y;
    bool small;
    bool black;
    uint32_t update_interval;
} Config;

Config *readConfig();

#endif

