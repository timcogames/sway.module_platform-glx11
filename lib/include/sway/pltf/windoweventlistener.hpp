#ifndef SWAY_PLTF_WINDOWEVENTLISTENER_HPP
#define SWAY_PLTF_WINDOWEVENTLISTENER_HPP

#include <sway/pltf/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class WindowEventListener {
protected:
  virtual void handleCreateNotifyEvent(const XEvent &event) {}

  virtual void handleConfigureNotifyEvent(const XEvent &event) {}

  virtual void handleExposeEvent(const XEvent &event) {}

  virtual void handleFocusInEvent(const XEvent &event) {}

  virtual void handleFocusOutEvent(const XEvent &event) {}
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WINDOWEVENTLISTENER_HPP
