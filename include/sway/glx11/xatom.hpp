#ifndef SWAY_GLX11_XATOM_HPP
#define SWAY_GLX11_XATOM_HPP

#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

enum { kAtom_WMState, kAtom_WMDeleteWindow, kAtom_WMLast };

enum {
  kAtom_NetWMState,
  kAtom_NetWMStateMaximizedVert,
  kAtom_NetWMStateMaximizedHorz,
  kAtom_NetWMStateFullscreen,
  kAtom_NetLast
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif
