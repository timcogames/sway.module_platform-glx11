#include <sway/pltf/mac/dtpwindow.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

DTPWindow::DTPWindow(DTPScreenConnectionRef_t connection)
    : connection_(connection) {
  initializeAtoms_();
  initializeEventBindings_();
}

DTPWindow::~DTPWindow() {
  if (window_) {
    XDestroyWindow(connection_->getDisplay(), window_);
    XFlush(connection_->getDisplay());
  }
}

void DTPWindow::initializeAtoms_() {
  wmatom_[kAtom_WMState] = XInternAtom(connection_->getDisplay(), "WM_STATE", False);
  wmatom_[kAtom_WMDeleteWindow] = XInternAtom(connection_->getDisplay(), "WM_DELETE_WINDOW", False);

  netatom_[kAtom_NetWMState] = XInternAtom(connection_->getDisplay(), "_NET_WM_STATE", False);
  netatom_[kAtom_NetWMStateMaximizedVert] =
      XInternAtom(connection_->getDisplay(), "_NET_WM_STATE_MAXIMIZED_VERT", False);
  netatom_[kAtom_NetWMStateMaximizedHorz] =
      XInternAtom(connection_->getDisplay(), "_NET_WM_STATE_MAXIMIZED_HORZ", False);
  netatom_[kAtom_NetWMStateFullscreen] = XInternAtom(connection_->getDisplay(), "_NET_WM_STATE_FULLSCREEN", False);
}

void DTPWindow::initializeEventBindings_() {
  eventCallbacks_.clear();

  addEventBinding(CreateNotify, std::bind(&DTPWindow::handleCreateNotifyEvent, this, std::placeholders::_1));
  addEventBinding(ConfigureNotify, std::bind(&DTPWindow::handleConfigureNotifyEvent, this, std::placeholders::_1));
  addEventBinding(Expose, std::bind(&DTPWindow::handleExposeEvent, this, std::placeholders::_1));
  addEventBinding(FocusIn, std::bind(&DTPWindow::handleFocusInEvent, this, std::placeholders::_1));
  addEventBinding(FocusOut, std::bind(&DTPWindow::handleFocusOutEvent, this, std::placeholders::_1));
}

void DTPWindow::addEventBinding(s32_t type, EventCallbackFunc_t callback) { eventCallbacks_[type] = callback; }

void DTPWindow::createDummy(XVisualInfo *visualInfo, const WindowInitialInfo &windowInfo) {
  XSetWindowAttributes attrs;
  attrs.background_pixel = attrs.border_pixel = BlackPixel(connection_->getDisplay(), connection_->getScreenNumber());
  attrs.colormap =
      XCreateColormap(connection_->getDisplay(), connection_->getRootWindow(), visualInfo->visual, AllocNone);
  attrs.event_mask = 0;
  attrs.event_mask |= EnterWindowMask | LeaveWindowMask;
  attrs.event_mask |= StructureNotifyMask;
  attrs.event_mask |= ExposureMask;
  attrs.event_mask |= FocusChangeMask;

  int const mask = CWBackPixel | CWBorderPixel | CWColormap | CWEventMask;

  window_ = XCreateWindow(connection_->getDisplay(), connection_->getRootWindow(), 0, 0, windowInfo.size.normal.getW(),
      windowInfo.size.normal.getH(), 0, visualInfo->depth, InputOutput, visualInfo->visual, mask, &attrs);
  if (window_ == None) {
    throw std::runtime_error("Couldn't create the window.");
  }

  XSelectInput(connection_->getDisplay(), window_,
      SubstructureNotifyMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask | KeyPressMask | KeyReleaseMask |
          KeymapStateMask);

  XSetWMProtocols(connection_->getDisplay(), window_, &wmatom_[kAtom_WMDeleteWindow], 1);
}

auto DTPWindow::eventLoop(bool keepgoing) -> bool {
  if (XPending(connection_->getDisplay()) != 0) {
    XEvent event = {};
    XNextEvent(connection_->getDisplay(), &event);

    auto iter = eventCallbacks_.find(event.type);
    if (iter != eventCallbacks_.end()) {
      iter->second(event);
    }

    if (event.type == ClientMessage) {
      if (event.xclient.format == 32 && Atom(event.xclient.data.l[0]) == wmatom_[kAtom_WMDeleteWindow]) {
        keepgoing = false;
      }
    }
  }

  return keepgoing;
}

void DTPWindow::setTitle(lpcstr_t title) {
  XStoreName(connection_->getDisplay(), window_, title);
  XFlush(connection_->getDisplay());
}

void DTPWindow::setPosition(s32_t x, s32_t y) {
  if (!visible()) {
    s64_t supplied;
    XSizeHints *hints = XAllocSizeHints();
    XGetWMNormalHints(connection_->getDisplay(), window_, hints, &supplied);

    hints->flags |= PPosition;
    hints->x = hints->y = 0;

    XSetWMNormalHints(connection_->getDisplay(), window_, hints);
    XFree(hints);
  }

  XMoveWindow(connection_->getDisplay(), window_, x, y);
  XFlush(connection_->getDisplay());
}

auto DTPWindow::getPosition() const -> math::point2i_t {
  Window dummy;
  s32_t xpos, ypos;
  XTranslateCoordinates(connection_->getDisplay(), window_, connection_->getRootWindow(), 0, 0, &xpos, &ypos, &dummy);
  return math::Point<s32_t>(xpos, ypos);
}

void DTPWindow::setSize(s32_t w, s32_t h) {
  XResizeWindow(connection_->getDisplay(), window_, w, h);
  XFlush(connection_->getDisplay());
}

auto DTPWindow::getSize() const -> math::size2i_t {
  XWindowAttributes attrs;
  XGetWindowAttributes(connection_->getDisplay(), window_, &attrs);
  return math::Size<s32_t>(attrs.width, attrs.height);
}

void DTPWindow::setMinSize_(XSizeHints *hints, const WindowSize &size, bool resizable) {
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

void DTPWindow::setMaxSize_(XSizeHints *hints, const WindowSize &size, bool resizable) {
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

void DTPWindow::setSizeHints(const WindowSize &size, bool resizable) {
  XSizeHints *hints = XAllocSizeHints();
  if (!hints) {
    fprintf(stderr, "Could not allocate memory for size hints.\n");
    return;
  }

  hints->flags |= (PMinSize | PMaxSize);

  setMinSize_(hints, size, resizable);
  setMaxSize_(hints, size, resizable);

  XSetWMNormalHints(connection_->getDisplay(), window_, hints);
  XFree(hints);
}

void DTPWindow::show() {
  if (!visible()) {
    XMapRaised(connection_->getDisplay(), window_);
    XFlush(connection_->getDisplay());
  }
}

void DTPWindow::hide() {
  XUnmapWindow(connection_->getDisplay(), window_);
  XFlush(connection_->getDisplay());
}

auto DTPWindow::visible() const -> bool {
  XWindowAttributes attrs;
  XGetWindowAttributes(connection_->getDisplay(), window_, &attrs);
  return (attrs.map_state == IsViewable);
}

void DTPWindow::setFullscreen(bool fullscreen) {
  XEvent event;
  event.type = ClientMessage;
  event.xclient.serial = 0;
  event.xclient.send_event = True;
  event.xclient.window = window_;
  event.xclient.message_type = netatom_[kAtom_NetWMState];
  event.xclient.format = 32;
  event.xclient.data.l[0] = core::detail::toUnderlying(fullscreen ? WindowMode::FULLSCREEN : WindowMode::WINDOWED);
  event.xclient.data.l[1] = netatom_[kAtom_NetWMStateFullscreen];
  event.xclient.data.l[2] = 0;

  XSendEvent(connection_->getDisplay(), connection_->getRootWindow(), False,
      SubstructureNotifyMask | SubstructureRedirectMask, &event);
}

void DTPWindow::setMaximize(bool maximized) {
  XEvent event;
  event.xclient.type = ClientMessage;
  event.xclient.window = window_;
  event.xclient.message_type = netatom_[kAtom_NetWMState];
  event.xclient.format = 32;
  event.xclient.data.l[0] = maximized ? 1 : 0;
  event.xclient.data.l[1] = 0;
  event.xclient.data.l[2] = 0;

  int i = 1;
  event.xclient.data.l[i++] = netatom_[kAtom_NetWMStateMaximizedVert];
  event.xclient.data.l[i++] = netatom_[kAtom_NetWMStateMaximizedHorz];

  XSendEvent(connection_->getDisplay(), connection_->getRootWindow(), False, SubstructureRedirectMask, &event);
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
