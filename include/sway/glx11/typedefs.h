#ifndef SWAY_GLX11_TYPEDEFS_H
#define SWAY_GLX11_TYPEDEFS_H

#include <sway/namespacemacros.h>
#include <sway/types.h>

#include <boost/shared_ptr.hpp> // boost::shared_ptr

#include <map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

typedef boost::shared_ptr<class XScreenConnection> XScreenConnectionRef_t;
typedef boost::shared_ptr<class GlxContext> GlxContextRef_t;
typedef boost::shared_ptr<class Canvas> CanvasRef_t;

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_TYPEDEFS_H
