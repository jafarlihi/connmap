#ifndef CAIRO_CONNMAP_H
#define CAIRO_CONNMAP_H

#include <cairo.h>
#include <cairo-xlib.h>
#include <stdbool.h>

void draw_world(cairo_surface_t *surface, char *mapName);
void draw_point(cairo_surface_t *surface, bool small, double latitude, double longitude);
void clear_surface(cairo_surface_t *surface);

#endif

