#ifndef SWAY_PLTF_WINDOWEVENTTYPES_HPP
#define SWAY_PLTF_WINDOWEVENTTYPES_HPP

#include <sway/core.hpp>

namespace sway::pltf {

// clang-format off
DECLARE_ENUM(WindowEventType, 
  SIZE_CHANGE,
  RESOLUTION_CHANGE,
  FULLSCREEN_CHANGE,
  SCREEN_CHANGE,
  FOCUS_CHANGE,
  CLOSE,
  SHOW,
  HIDE,
  MINIMIZE,
  MAXIMIZE,
  RESTORE
);
// clang-format on

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WINDOWEVENTTYPES_HPP
