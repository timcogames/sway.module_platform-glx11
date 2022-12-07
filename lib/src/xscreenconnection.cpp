#include <sway/glx11/xscreenconnection.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

XScreenConnection::XScreenConnection() {
  _display = XOpenDisplay(NULL);
  if (_display == NULL) {
    throw core::runtime::Exception("Cannot connect to X server");
  }

  _screen = DefaultScreen(_display);
}

XScreenConnection::~XScreenConnection() {
  if (_display)
    XCloseDisplay(_display);
}

auto XScreenConnection::getDisplay() const -> Display * { return _display; }

auto XScreenConnection::getScreenNumber() const -> s32_t { return _screen; }

auto XScreenConnection::getRootWindow() const -> Window { return RootWindow(_display, _screen); }

auto XScreenConnection::getDisplaySize() const -> math::size2i_t {
  return math::TSize<s32_t>(DisplayWidth(_display, _screen), DisplayHeight(_display, _screen));
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)
