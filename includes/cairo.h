#ifndef CAIRO_CONNMAP_H
#define CAIRO_CONNMAP_H

#include <cairo.h>
#include <cairo-xlib.h>
#include <stdbool.h>

#define RESOURCES "/.connmap/resources/"

void cairo_close_x11_surface(cairo_surface_t *surface);
void draw_world(cairo_surface_t *surface, char *mapName);
void draw_point(cairo_surface_t *surface, bool small, int x, int y);
void clear_surface(cairo_surface_t *surface);

#endif

