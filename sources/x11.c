#include "x11.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

X11Details initX11(uint32_t location_x, uint32_t location_y, uint32_t size_x, uint32_t size_y) {
    Display *display = XOpenDisplay(NULL);

    if (display == NULL) {
        printf("\nCannot connect to X server\n");
        exit(1);
    }

    int screen = XDefaultScreen(display);
    Window root = DefaultRootWindow(display);

    XVisualInfo vinfo;
    XMatchVisualInfo(display, screen, 32, TrueColor, &vinfo);

    XSetWindowAttributes attrs;
    attrs.colormap = XCreateColormap(display, root, vinfo.visual, AllocNone);
    attrs.override_redirect = 1;
    attrs.background_pixel = 0;
    attrs.border_pixel = 0;

    Window window = XCreateWindow(display,
            root,
            location_x,
            location_y,
            size_x,
            size_y,
            0,
            vinfo.depth,
            InputOutput,
            vinfo.visual,
            CWOverrideRedirect | CWColormap | CWBackPixel | CWBorderPixel,
            &attrs);

    XMapWindow(display, window);

    XRectangle rect;
    XserverRegion region = XFixesCreateRegion(display, &rect, 1);
    XFixesSetWindowShapeRegion(display, window, ShapeInput, 0, 0, region);
    XFixesDestroyRegion(display, region);

    XClassHint *xch = XAllocClassHint();
    xch->res_name = "connmap";
    xch->res_class = "connmap";
    XSetClassHint(display, window, xch);

    XLowerWindow(display, window);

    return (X11Details) {.display = display, .window = window, .vinfo = vinfo};
}

