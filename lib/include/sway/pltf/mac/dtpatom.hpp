#ifndef SWAY_PLTF_MAC_DTPATOM_HPP
#define SWAY_PLTF_MAC_DTPATOM_HPP

#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

enum { kAtom_WMState, kAtom_WMDeleteWindow, kAtom_WMLast };

enum {
  kAtom_NetWMState,
  kAtom_NetWMStateMaximizedVert,
  kAtom_NetWMStateMaximizedHorz,
  kAtom_NetWMStateFullscreen,
  kAtom_NetLast
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_MAC_DTPATOM_HPP
