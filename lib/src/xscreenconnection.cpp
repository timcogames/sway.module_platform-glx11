#include <sway/glx11/xscreenconnection.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

XScreenConnection::XScreenConnection() {
  display_ = XOpenDisplay(NULL);
  if (display_ == NULL) {
    throw core::runtime::Exception("Cannot connect to X server");
  }

  screen_ = DefaultScreen(display_);
}

XScreenConnection::~XScreenConnection() {
  if (display_) {
    XCloseDisplay(display_);
  }
}

auto XScreenConnection::getDisplay() const -> Display * { return display_; }

auto XScreenConnection::getScreenNumber() const -> s32_t { return screen_; }

auto XScreenConnection::getRootWindow() const -> Window { return RootWindow(display_, screen_); }

auto XScreenConnection::getDisplaySize() const -> math::size2i_t {
  return math::Size<s32_t>(DisplayWidth(display_, screen_), DisplayHeight(display_, screen_));
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)
