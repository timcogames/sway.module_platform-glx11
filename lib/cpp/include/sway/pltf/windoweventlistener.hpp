#ifndef SWAY_PLTF_WINDOWEVENTLISTENER_HPP
#define SWAY_PLTF_WINDOWEVENTLISTENER_HPP

#include <sway/pltf/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class WindowEventListener {
protected:
  MTHD_VIRTUAL(void handleCreateNotifyEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleConfigureNotifyEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleExposeEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleFocusInEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleFocusOutEvent(const XEvent &event){})
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WINDOWEVENTLISTENER_HPP
