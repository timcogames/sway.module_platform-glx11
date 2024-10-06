#ifndef SWAY_PLTF_MAC_DTPATOM_HPP
#define SWAY_PLTF_MAC_DTPATOM_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

enum { kAtom_WMState, kAtom_WMDeleteWindow, kAtom_WMLast };

enum {
  kAtom_NetWMState,
  kAtom_NetWMStateMaximizedVert,
  kAtom_NetWMStateMaximizedHorz,
  kAtom_NetWMStateFullscreen,
  kAtom_NetLast
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_MAC_DTPATOM_HPP
