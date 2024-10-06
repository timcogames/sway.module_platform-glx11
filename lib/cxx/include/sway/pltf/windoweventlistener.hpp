#ifndef SWAY_PLTF_WINDOWEVENTLISTENER_HPP
#define SWAY_PLTF_WINDOWEVENTLISTENER_HPP

#include <sway/pltf/prereqs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class WindowEventListener {
protected:
  MTHD_VIRTUAL(void handleCreateNotifyEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleConfigureNotifyEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleExposeEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleFocusInEvent(const XEvent &event){})

  MTHD_VIRTUAL(void handleFocusOutEvent(const XEvent &event){})
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_WINDOWEVENTLISTENER_HPP
