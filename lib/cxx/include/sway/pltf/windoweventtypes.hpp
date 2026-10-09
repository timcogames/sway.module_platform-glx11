#ifndef SWAY_PLTF_WINDOWEVENTTYPES_HPP
#define SWAY_PLTF_WINDOWEVENTTYPES_HPP

#include <sway/core.hpp>

namespace sway::pltf {

// clang-format off
#define WINDOW_EVENT_TYPE_LIST(ITEM) \
  ITEM(SIZE_CHANGE, 1) \
  ITEM(RESOLUTION_CHANGE, 2) \
  ITEM(FULLSCREEN_CHANGE, 3) \
  ITEM(SCREEN_CHANGE, 4) \
  ITEM(FOCUS_CHANGE, 5) \
  ITEM(CLOSE, 6) \
  ITEM(SHOW, 7) \
  ITEM(HIDE, 8) \
  ITEM(MINIMIZE, 9) \
  ITEM(MAXIMIZE, 10) \
  ITEM(RESTORE, 11)
// clang-format on

DECLARE_ENUM_U32(WindowEventType, WINDOW_EVENT_TYPE_LIST)

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WINDOWEVENTTYPES_HPP
