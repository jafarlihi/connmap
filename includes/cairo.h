#ifndef CAIRO_CONNMAP_H
#define CAIRO_CONNMAP_H

#include <cairo.h>
#include <cairo-xlib.h>
#include <stdbool.h>

void draw_world(cairo_surface_t *surface, char *mapName);
void draw_point(cairo_surface_t *surface, bool small, int x, int y);
void clear_surface(cairo_surface_t *surface);

#endif

