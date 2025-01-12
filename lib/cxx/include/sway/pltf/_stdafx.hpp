#ifndef SWAY_PLTF_STDAFX_HPP
#define SWAY_PLTF_STDAFX_HPP

#include <sway/core.hpp>
#include <sway/math.hpp>

#ifdef EMSCRIPTEN_PLATFORM
#  include <emscripten.h>
#  include <emscripten/html5.h>
#else
#  include <X11/Xlib.h>
#  include <X11/Xutil.h>  // XVisualInfo, XSizeHints
#  include <chrono>
#endif

#include <GL/gl.h>
#include <GL/glx.h>  // GLXContext, GLXDrawable, GLXFBConfig
#include <condition_variable>
#include <functional>
#include <map>
#include <memory>  // shared_ptr, make_shared
#include <mutex>
#include <queue>
#include <string>

#endif  // SWAY_PLTF_STDAFX_HPP
