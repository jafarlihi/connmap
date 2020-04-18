#include "config.h"
#include "x11.h"
#include "cairo.h"
#include "ip.h"
#include "geo.h"
#include "ss.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    Config *config = readConfig();
    int size_x, size_y;
    char *mapName = malloc(sizeof(char) * 10);
    if (config->small == true) {
        size_x = 500;
        size_y = 250;
        mapName = strcpy(mapName, "w500.png");
    } else {
        size_x = 1000;
        size_y = 500;
        mapName = strcpy(mapName, "w1000.png");
    }

    char mapFilename[256];
    strcat(strcpy(mapFilename, getenv("HOME")), RESOURCES);
    strcat(mapFilename, mapName);

    initCoordinateDatabase();
    initIPDatabase();
    X11Details x11 = initX11(config->location_x, config->location_y, size_x, size_y);
    cairo_surface_t *surface = cairo_xlib_surface_create(x11.display, x11.window, DefaultVisual(x11.display, DefaultScreen(x11.display)), size_x, size_y);
    cairo_xlib_surface_set_size(surface, size_x, size_y);

    while (1) {
        clear_surface(surface);
        draw_world(surface, mapFilename);

        refreshConnections();

        char *ip;
        while ((ip = getConnection()) != NULL) {
            char *countryCode = getCountryCode(ip);
            if (countryCode == NULL) continue;
            Coord *coord = getCoord(countryCode);
            draw_point(surface, config->small, coord->x, coord->y);
            free(ip);
        }

        sleep(config->update_interval);
    }

    Display *display = cairo_xlib_surface_get_display(surface);
    cairo_surface_destroy(surface);
    XCloseDisplay(display);
    return 0;
}

