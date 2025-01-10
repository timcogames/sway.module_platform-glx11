#ifndef SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP
#define SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP

#include <sway/core.hpp>

namespace sway::pltf {

struct DTPVisualAttributes {
  i32_t numMultisample;
  i32_t numSamples;
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_MAC_DTPVISUALATTRIBUTES_HPP
