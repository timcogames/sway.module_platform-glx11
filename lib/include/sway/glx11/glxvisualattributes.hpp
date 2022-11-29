#ifndef SWAY_GLX11_GLXVISUALATTRIBUTES_HPP
#define SWAY_GLX11_GLXVISUALATTRIBUTES_HPP

#include <sway/namespacemacros.hpp>
#include <sway/types.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct GlxVisualAttributes {
  s32_t numMultisample;
  s32_t numSamples;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif  // SWAY_GLX11_GLXVISUALATTRIBUTES_HPP
