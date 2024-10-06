#ifndef SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP
#define SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

struct DTPVisualAttributes {
  i32_t numMultisample;
  i32_t numSamples;
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP
