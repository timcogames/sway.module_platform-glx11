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

Display *XScreenConnection::getDisplay() const { return _display; }

s32_t XScreenConnection::getScreenNumber() const { return _screen; }

Window XScreenConnection::getRootWindow() const { return RootWindow(_display, _screen); }

math::size2i_t XScreenConnection::getDisplaySize() const {
  return math::TSize<s32_t>(DisplayWidth(_display, _screen), DisplayHeight(_display, _screen));
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)
