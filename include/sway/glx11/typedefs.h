#ifndef SWAY_GLX11_TYPEDEFS_H
#define SWAY_GLX11_TYPEDEFS_H

#include <sway/namespacemacros.h>
#include <sway/types.h>

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/function.hpp> // boost::function

#include <map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

typedef boost::shared_ptr<class XScreenConnection> XScreenConnectionRef_t;
typedef boost::shared_ptr<class GlxContext> GlxContextRef_t;
typedef boost::function<void (const XEvent &)> EventCallbackFunc_t;
typedef std::map<s32_t, EventCallbackFunc_t> EventCallbackFuncMap_t;

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_TYPEDEFS_H
