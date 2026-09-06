#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <stdio.h>
#include <stdlib.h>

/* Stubs for libX11 transport functions to satisfy xkbcomp linker requirements when building without XCB */

Status _XReply(Display *dpy, xReply *rep, int extra, Bool discard) {
    fprintf(stderr, "xkbcomp stub: _XReply called\n");
    return 0;
}

int _XRead(Display *dpy, char *data, long size) {
    fprintf(stderr, "xkbcomp stub: _XRead called\n");
    return 0;
}

void _XReadPad(Display *dpy, char *data, long size) {
    fprintf(stderr, "xkbcomp stub: _XReadPad called\n");
}

void _XEatData(Display *dpy, unsigned long n) {
    fprintf(stderr, "xkbcomp stub: _XEatData called\n");
}

void _XEatDataWords(Display *dpy, unsigned long n) {
    fprintf(stderr, "xkbcomp stub: _XEatDataWords called\n");
}

void _XFlush(Display *dpy) {
    /* No-op */
}

void _XSend(Display *dpy, const char *data, long size) {
    fprintf(stderr, "xkbcomp stub: _XSend called\n");
}

void _XIDHandler(Display *dpy) {
    /* No-op */
}

/* XID allocation stub */
XID _XAllocID(Display *dpy) {
    static XID fake_id = 100;
    return fake_id++;
}
