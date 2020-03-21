#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "config.h"
#include "x11.h"
#include "cairo.h"
#include "ip.h"
#include "geo.h"
#include "ss.h"

int main(int argc, char **argv) {
    Config *config = readConfig();
    int size_x, size_y;
    char *mapName = malloc(sizeof(char) * 10);
    if (config->small == true) {
        size_x = 500;
        size_y = 250;
        if (config->white == true) {
            mapName = strcpy(mapName, "w500.png");
        } else {
            mapName = strcpy(mapName, "b500.png");
        }
    } else {
        size_x = 1000;
        size_y = 500;
        if (config->white == true) {
            mapName = strcpy(mapName, "w1000.png");
        } else {
            mapName = strcpy(mapName, "b1000.png");
        }
    }

    initIPDatabase();
    X11Details x11 = initX11(config->location_x, config->location_y, size_x, size_y);
    cairo_surface_t *surface = cairo_xlib_surface_create(x11.display, x11.window, DefaultVisual(x11.display, DefaultScreen(x11.display)), size_x, size_y);
    cairo_xlib_surface_set_size(surface, size_x, size_y);

    while (1) {
        clear_surface(surface);
        draw_world(surface, mapName);

        refreshConnections();

        char *ip;
        while ((ip = getConnection()) != NULL) {
            char *countryCode = getCountryCode(ip);
            if (countryCode == NULL) continue;
            Coord coord = getCoord(countryCode);
            draw_point(surface, config->small, coord.x, coord.y);
            free(ip);
        }

        sleep(config->update_interval);
    }

    cairo_close_x11_surface(surface);
    return 0;
}

