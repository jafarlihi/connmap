#include "cairo.h"

#include <stdlib.h>
#include <string.h>

void cairo_close_x11_surface(cairo_surface_t *surface) {
    Display *display = cairo_xlib_surface_get_display(surface);
    cairo_surface_destroy(surface);
    XCloseDisplay(display);
}

void draw_world(cairo_surface_t *surface, char *mapFilename) {
    cairo_t *context = cairo_create(surface);
    cairo_set_source_rgba(context, 0.0, 0.0, 0.0, 0.0);
    cairo_paint(context);
    cairo_surface_t *world = cairo_image_surface_create_from_png(mapFilename);
    cairo_set_source_surface(context, world, 0, 0);
    cairo_paint(context);
    cairo_destroy(context);
}

void draw_point(cairo_surface_t *surface, bool small, int x, int y) {
    cairo_t *context = cairo_create(surface);
    cairo_set_source_rgba(context, 0.0, 0.0, 0.0, 0.0);
    cairo_paint(context);
    cairo_set_source_rgba(context, 1, 0.2, 0.2, 0.8);
    cairo_set_line_width(context, 3.0);
    if (small)
        cairo_arc(context, x/2, y/2, 4.0, 0, 2*3.14);
    else
        cairo_arc(context, x, y, 8.0, 0, 2*3.14);
    cairo_fill(context);
    cairo_destroy(context);
}

void draw_invisible_point(cairo_surface_t *surface) {
    cairo_t *context = cairo_create(surface);
    cairo_set_source_rgba(context, 0.0, 0.0, 0.0, 0.0);
    cairo_paint(context);
    cairo_set_source_rgba(context, 0, 0, 0, 1);
    cairo_set_line_width(context, 1.0);
    cairo_arc(context, 0, 0, 1.0, 0, 2*3.14);
    cairo_fill(context);
    cairo_destroy(context);
}

void clear_surface(cairo_surface_t *surface) {
    cairo_t *context = cairo_create(surface);
    cairo_set_source_rgba(context, 0, 0, 0, 0);
    cairo_set_operator(context, CAIRO_OPERATOR_SOURCE);
    cairo_paint(context);
    cairo_destroy(context);
    draw_invisible_point(surface);
}

