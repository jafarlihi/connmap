#ifndef X11_H
#define X11_H

#include <X11/Xlib.h>

typedef struct X11Details {
    Display *display;
    Window window;
} X11Details;

X11Details initX11();

#endif

