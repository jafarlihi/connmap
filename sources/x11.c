#include "x11.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

X11Details initX11(uint32_t location_x, uint32_t location_y, uint32_t size_x, uint32_t size_y) {
    Display *display = XOpenDisplay(NULL);

    if (display == NULL) {
        printf("\nCannot connect to X server\n");
        exit(0);
    }

    int screen = DefaultScreen(display);
    Window root = DefaultRootWindow(display);
    Colormap colormap = XCreateColormap(display, root, DefaultVisual(display, screen), AllocNone);

    XSetWindowAttributes attrs;
    attrs.colormap = colormap;
    attrs.event_mask = ExposureMask;
    attrs.background_pixmap = ParentRelative;
    attrs.backing_store = Always;
    attrs.save_under = False;
    attrs.override_redirect = True;

    unsigned long flags = CWColormap | CWEventMask | CWOverrideRedirect | CWBackingStore;

    Window window = XCreateWindow(display,
            root,
            location_x, location_y,
            size_x, size_y,
            0,
            DefaultDepth(display, screen),
            InputOutput,
            DefaultVisual(display, screen),
            flags,
            &attrs);

    XLowerWindow(display, window);
    XMapWindow(display, window);

    return (X11Details) {.display = display, .window = window};
}

