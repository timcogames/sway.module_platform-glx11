#ifndef SWAY_PLTF_MAC_DTPATOM_HPP
#define SWAY_PLTF_MAC_DTPATOM_HPP

#include <sway/core.hpp>

namespace sway::pltf {

enum { kAtom_WMState, kAtom_WMDeleteWindow, kAtom_WMLast };

enum {
  kAtom_NetWMState,
  kAtom_NetWMStateMaximizedVert,
  kAtom_NetWMStateMaximizedHorz,
  kAtom_NetWMStateFullscreen,
  kAtom_NetLast
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_MAC_DTPATOM_HPP
