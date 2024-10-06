#include <sway/pltf/mac/dtpscreenconnection.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

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

auto DTPScreenConnection::getScreenNumber() const -> i32_t { return screen_; }

auto DTPScreenConnection::getRootWindow() const -> Window { return RootWindow(display_, screen_); }

auto DTPScreenConnection::getDisplaySize() const -> math::size2i_t {
  return math::Size<i32_t>(DisplayWidth(display_, screen_), DisplayHeight(display_, screen_));
}

NS_END()  // namespace pltf
NS_END()  // namespace sway
