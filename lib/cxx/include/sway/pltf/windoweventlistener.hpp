#ifndef SWAY_PLTF_WINDOWEVENTLISTENER_HPP
#define SWAY_PLTF_WINDOWEVENTLISTENER_HPP

#include <sway/pltf/_stdafx.hpp>

namespace sway::pltf {

class WindowEventListener {
protected:
  MTHD_VIRTUAL(
      void handleCreateNotifyEvent(const XEvent &event) {})

  MTHD_VIRTUAL(
      void handleConfigureNotifyEvent(const XEvent &event) {})

  MTHD_VIRTUAL(
      void handleExposeEvent(const XEvent &event) {})

  MTHD_VIRTUAL(
      void handleFocusInEvent(const XEvent &event) {})

  MTHD_VIRTUAL(
      void handleFocusOutEvent(const XEvent &event) {})
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WINDOWEVENTLISTENER_HPP
