#ifndef SWAY_GLX11_TYPEDEFS_HPP
#define SWAY_GLX11_TYPEDEFS_HPP

#include <sway/namespacemacros.hpp>
#include <sway/types.hpp>

#include <map>
#include <memory>  // std::shared_ptr

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

typedef std::shared_ptr<class XScreenConnection> XScreenConnectionRef_t;
typedef std::shared_ptr<class GlxContext> GlxContextRef_t;
typedef std::shared_ptr<class Canvas> CanvasRef_t;

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif
