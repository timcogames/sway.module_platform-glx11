#ifndef SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP
#define SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

struct DTPVisualAttributes {
  s32_t numMultisample;
  s32_t numSamples;
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP
