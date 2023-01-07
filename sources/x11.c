#include "x11.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <X11/extensions/shape.h>
#include <X11/extensions/Xfixes.h>

X11Details initX11(uint32_t location_x, uint32_t location_y, uint32_t size_x, uint32_t size_y) {
    bool disable_redirect_override = False;
    char *xdg_current_desktop = getenv("XDG_CURRENT_DESKTOP");
    if (xdg_current_desktop != NULL && strlen(xdg_current_desktop) > 0) {
        for (; *xdg_current_desktop; ++xdg_current_desktop)
            *xdg_current_desktop = tolower(*xdg_current_desktop);
        if (strstr("kde", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("gnome", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("xfce", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("lxde", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("lxqt", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("mate", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("enlightenment", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("deepin", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
        if (strstr("cinnamon", xdg_current_desktop) != NULL)
            disable_redirect_override = True;
    }

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

    unsigned long value_mask = CWColormap | CWBackPixel | CWBorderPixel;
    if (!disable_redirect_override)
        value_mask |= CWOverrideRedirect;

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
            value_mask,
            &attrs);

    if (disable_redirect_override) {
        Atom window_type = XInternAtom(display, "_NET_WM_WINDOW_TYPE", 0);
        Atom window_type_desktop = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DESKTOP", 0);
        XChangeProperty(display, window, window_type, XA_ATOM, 32, PropModeReplace, (unsigned char *)&window_type_desktop, 1);

        double alpha = 0.99;
        unsigned long opacity = (unsigned long)(0xFFFFFFFFul * alpha);
        Atom window_opacity = XInternAtom(display, "_NET_WM_WINDOW_OPACITY", False);
        XChangeProperty(display, window, window_opacity, XA_CARDINAL, 32, PropModeReplace, (unsigned char *)&opacity, 1);
    }

    XMapWindow(display, window);

    XRectangle rect;
    XserverRegion region = XFixesCreateRegion(display, &rect, 1);
    XFixesSetWindowShapeRegion(display, window, ShapeInput, 0, 0, region);
    XFixesDestroyRegion(display, region);

    XClassHint *xch = XAllocClassHint();
    xch->res_name = "connmap";
    xch->res_class = "connmap";
    XSetClassHint(display, window, xch);

    if (!disable_redirect_override)
        XLowerWindow(display, window);

    return (X11Details) {.display = display, .window = window, .vinfo = vinfo};
}

