#ifndef SWAY_GLX11_WINDOWEVENTLISTENER_HPP
#define SWAY_GLX11_WINDOWEVENTLISTENER_HPP

#include <sway/glx11/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class WindowEventListener {
protected:
  virtual void handleCreateNotifyEvent(const XEvent &event) {
    // Empty
  }

  virtual void handleConfigureNotifyEvent(const XEvent &event) {
    // Empty
  }

  virtual void handleExposeEvent(const XEvent &event) {
    // Empty
  }

  virtual void handleFocusInEvent(const XEvent &event) {
    // Empty
  }

  virtual void handleFocusOutEvent(const XEvent &event) {
    // Empty
  }
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif
