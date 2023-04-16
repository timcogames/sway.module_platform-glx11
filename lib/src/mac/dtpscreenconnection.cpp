#include <sway/pltf/mac/dtpscreenconnection.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

DTPScreenConnection::DTPScreenConnection() {
  display_ = XOpenDisplay(NULL);
  if (display_ == NULL) {
    throw core::runtime::Exception("Cannot connect to X server");
  }

  screen_ = DefaultScreen(display_);
}

DTPScreenConnection::~DTPScreenConnection() {
  if (display_) {
    XCloseDisplay(display_);
  }
}

auto DTPScreenConnection::getDisplay() const -> Display * { return display_; }

auto DTPScreenConnection::getScreenNumber() const -> s32_t { return screen_; }

auto DTPScreenConnection::getRootWindow() const -> Window { return RootWindow(display_, screen_); }

auto DTPScreenConnection::getDisplaySize() const -> math::size2i_t {
  return math::Size<s32_t>(DisplayWidth(display_, screen_), DisplayHeight(display_, screen_));
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
