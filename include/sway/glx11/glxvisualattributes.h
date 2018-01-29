#ifndef SWAY_GLX11_GLXVISUALATTRIBUTES_H
#define SWAY_GLX11_GLXVISUALATTRIBUTES_H

#include <sway/namespacemacros.h>
#include <sway/types.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct GlxVisualAttributes {
	s32_t numMultisample;
	s32_t numSamples;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_GLXVISUALATTRIBUTES_H
