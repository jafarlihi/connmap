#include "cairo.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>

#define PI 3.14159265

void draw_invisible_point(cairo_surface_t *surface) {
    cairo_t *context = cairo_create(surface);
    cairo_set_source_rgba(context, 0, 0, 0, 1);
    cairo_set_line_width(context, 1.0);
    cairo_arc(context, 0, 0, 1.0, 0, 2*3.14);
    cairo_fill(context);
    cairo_destroy(context);
}

void draw_world(cairo_surface_t *surface, char *mapFilename) {
    cairo_t *context = cairo_create(surface);
    cairo_surface_t *world = cairo_image_surface_create_from_png(mapFilename);
    cairo_set_source_surface(context, world, 0, 0);
    cairo_paint(context);
    cairo_surface_destroy(world);
    cairo_destroy(context);
    draw_invisible_point(surface);
}

void draw_point(cairo_surface_t *surface, bool small, double latitude, double longitude) {
    cairo_t *context = cairo_create(surface);
    cairo_set_source_rgba(context, 1, 0.2, 0.2, 0.8);
    cairo_set_line_width(context, 3.0);

    double dotRadius = small ? 4.0 : 8.0;
    double width = small ? 500 : 1000;
    double height = small ? 250 : 500;

    uint32_t xOffset = small ? -14 : -29;
    uint32_t yOffset = small ? 38 : 76;

    double x = (longitude + 180) * (width / 360) + xOffset;
    double latRad = latitude * PI / 180;
    double mercN = log(tan((PI / 4) + (latRad / 2)));
    double y = (height / 2) - (width * mercN / (2 * PI)) + yOffset;

    cairo_arc(context, x, y, dotRadius, 0, 2 * PI);
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

