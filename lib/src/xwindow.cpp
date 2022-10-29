#include <sway/glx11/xwindow.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

XWindow::XWindow(XScreenConnectionRef_t connection)
    : _connection(connection) {

  _initializeAtoms();
  _initializeEventBindings();
}

XWindow::~XWindow() {
  if (_window) {
    XDestroyWindow(_connection->getDisplay(), _window);
    XFlush(_connection->getDisplay());
  }
}

void XWindow::_initializeAtoms() {
  _wmatom[kAtom_WMState] = XInternAtom(_connection->getDisplay(), "WM_STATE", False);
  _wmatom[kAtom_WMDeleteWindow] = XInternAtom(_connection->getDisplay(), "WM_DELETE_WINDOW", False);

  _netatom[kAtom_NetWMState] = XInternAtom(_connection->getDisplay(), "_NET_WM_STATE", False);
  _netatom[kAtom_NetWMStateMaximizedVert] =
      XInternAtom(_connection->getDisplay(), "_NET_WM_STATE_MAXIMIZED_VERT", False);
  _netatom[kAtom_NetWMStateMaximizedHorz] =
      XInternAtom(_connection->getDisplay(), "_NET_WM_STATE_MAXIMIZED_HORZ", False);
  _netatom[kAtom_NetWMStateFullscreen] = XInternAtom(_connection->getDisplay(), "_NET_WM_STATE_FULLSCREEN", False);
}

void XWindow::_initializeEventBindings() {
  _eventCallbacks.clear();

  addEventBinding(CreateNotify, std::bind(&XWindow::handleCreateNotifyEvent, this, std::placeholders::_1));
  addEventBinding(ConfigureNotify, std::bind(&XWindow::handleConfigureNotifyEvent, this, std::placeholders::_1));
  addEventBinding(Expose, std::bind(&XWindow::handleExposeEvent, this, std::placeholders::_1));
  addEventBinding(FocusIn, std::bind(&XWindow::handleFocusInEvent, this, std::placeholders::_1));
  addEventBinding(FocusOut, std::bind(&XWindow::handleFocusOutEvent, this, std::placeholders::_1));
}

void XWindow::addEventBinding(s32_t type, EventCallbackFunc_t callback) { _eventCallbacks[type] = callback; }

void XWindow::createDummy(XVisualInfo *visualInfo, const WindowInitialInfo &windowInfo) {
  XSetWindowAttributes attrs;
  attrs.background_pixel = attrs.border_pixel = BlackPixel(_connection->getDisplay(), _connection->getScreenNumber());
  attrs.colormap =
      XCreateColormap(_connection->getDisplay(), _connection->getRootWindow(), visualInfo->visual, AllocNone);
  attrs.event_mask = 0;
  attrs.event_mask |= EnterWindowMask | LeaveWindowMask;
  attrs.event_mask |= StructureNotifyMask;
  attrs.event_mask |= ExposureMask;
  attrs.event_mask |= FocusChangeMask;

  int mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

  _window = XCreateWindow(_connection->getDisplay(), _connection->getRootWindow(), 0, 0, windowInfo.size.normal.getW(),
      windowInfo.size.normal.getH(), 0, visualInfo->depth, InputOutput, visualInfo->visual, mask, &attrs);
  if (_window == None) {
    throw std::runtime_error("Couldn't create the window.");
  }

  XSelectInput(_connection->getDisplay(), _window,
      SubstructureNotifyMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask | KeyReleaseMask |
          KeymapStateMask);

  XSetWMProtocols(_connection->getDisplay(), _window, &_wmatom[kAtom_WMDeleteWindow], 1);
}

bool XWindow::eventLoop(bool keepgoing) {
  XEvent event = {};
  XNextEvent(_connection->getDisplay(), &event);

  EventCallbackFuncMap_t::const_iterator i = _eventCallbacks.find(event.type);
  if (i != _eventCallbacks.end()) {
    i->second(event);
  }

  if (event.type == ClientMessage) {
    if (event.xclient.format == 32 && Atom(event.xclient.data.l[0]) == _wmatom[kAtom_WMDeleteWindow]) {
      keepgoing = false;
    }
  }

  return keepgoing;
}

void XWindow::setTitle(lpcstr_t title) {
  XStoreName(_connection->getDisplay(), _window, title);
  XFlush(_connection->getDisplay());
}

void XWindow::setPosition(s32_t x, s32_t y) {
  if (!visible()) {
    s64_t supplied;
    XSizeHints *hints = XAllocSizeHints();
    XGetWMNormalHints(_connection->getDisplay(), _window, hints, &supplied);

    hints->flags |= PPosition;
    hints->x = hints->y = 0;

    XSetWMNormalHints(_connection->getDisplay(), _window, hints);
    XFree(hints);
  }

  XMoveWindow(_connection->getDisplay(), _window, x, y);
  XFlush(_connection->getDisplay());
}

math::point2i_t XWindow::getPosition() const {
  Window dummy;
  s32_t xpos, ypos;
  XTranslateCoordinates(_connection->getDisplay(), _window, _connection->getRootWindow(), 0, 0, &xpos, &ypos, &dummy);
  return math::TPoint<s32_t>(xpos, ypos);
}

void XWindow::setSize(s32_t w, s32_t h) {
  XResizeWindow(_connection->getDisplay(), _window, w, h);
  XFlush(_connection->getDisplay());
}

math::size2i_t XWindow::getSize() const {
  XWindowAttributes attrs;
  XGetWindowAttributes(_connection->getDisplay(), _window, &attrs);
  return math::TSize<s32_t>(attrs.width, attrs.height);
}

void XWindow::_setMinSize(XSizeHints *hints, const WindowSize &size, bool resizable) {
  if (resizable) {
    if (size.min.getW() != DONT_CARE && size.min.getH() != DONT_CARE) {
      hints->min_width = size.min.getW();
      hints->min_height = size.min.getH();
    } else {
      hints->flags = hints->flags & ~PMinSize;
      printf("Could not set minimum window size\n");
    }
  } else {
    hints->min_width = size.normal.getW();
    hints->min_height = size.normal.getH();
  }
}

void XWindow::_setMaxSize(XSizeHints *hints, const WindowSize &size, bool resizable) {
  if (resizable) {
    if (size.max.getW() != DONT_CARE && size.max.getH() != DONT_CARE) {
      hints->max_width = size.max.getW();
      hints->max_height = size.max.getH();
    } else {
      hints->flags = hints->flags & ~PMaxSize;
      printf("Could not set maximum window size\n");
    }
  } else {
    hints->max_width = size.normal.getW();
    hints->max_height = size.normal.getH();
  }
}

void XWindow::setSizeHints(const WindowSize &size, bool resizable) {
  XSizeHints *hints = XAllocSizeHints();
  if (!hints) {
    fprintf(stderr, "Could not allocate memory for size hints.\n");
    return;
  }

  hints->flags |= (PMinSize | PMaxSize);

  _setMinSize(hints, size, resizable);
  _setMaxSize(hints, size, resizable);

  XSetWMNormalHints(_connection->getDisplay(), _window, hints);
  XFree(hints);
}

void XWindow::show() {
  if (!visible()) {
    XMapRaised(_connection->getDisplay(), _window);
    XFlush(_connection->getDisplay());
  }
}

void XWindow::hide() {
  XUnmapWindow(_connection->getDisplay(), _window);
  XFlush(_connection->getDisplay());
}

bool XWindow::visible() const {
  XWindowAttributes attrs;
  XGetWindowAttributes(_connection->getDisplay(), _window, &attrs);
  return (attrs.map_state == IsViewable);
}

void XWindow::setFullscreen(bool fullscreen) {
  XEvent event;
  event.type = ClientMessage;
  event.xclient.serial = 0;
  event.xclient.send_event = True;
  event.xclient.window = _window;
  event.xclient.message_type = _netatom[kAtom_NetWMState];
  event.xclient.format = 32;
  event.xclient.data.l[0] =
      core::detail::toUnderlying(fullscreen ? WindowMode_t::kFullscreen : WindowMode_t::kWindowed);
  event.xclient.data.l[1] = _netatom[kAtom_NetWMStateFullscreen];
  event.xclient.data.l[2] = 0;

  XSendEvent(_connection->getDisplay(), _connection->getRootWindow(), False,
      SubstructureNotifyMask | SubstructureRedirectMask, &event);
}

void XWindow::setMaximize(bool maximized) {
  XEvent event;
  event.xclient.type = ClientMessage;
  event.xclient.window = _window;
  event.xclient.message_type = _netatom[kAtom_NetWMState];
  event.xclient.format = 32;
  event.xclient.data.l[0] = maximized ? 1 : 0;
  event.xclient.data.l[1] = 0;
  event.xclient.data.l[2] = 0;

  int i = 1;
  event.xclient.data.l[i++] = _netatom[kAtom_NetWMStateMaximizedVert];
  event.xclient.data.l[i++] = _netatom[kAtom_NetWMStateMaximizedHorz];

  XSendEvent(_connection->getDisplay(), _connection->getRootWindow(), False, SubstructureRedirectMask, &event);
}

Window XWindow::getWindowHandle() { return _window; }

NAMESPACE_END(glx11)
NAMESPACE_END(sway)
