#ifndef SWAY_PLTF_LOOPEABLE_HPP
#define SWAY_PLTF_LOOPEABLE_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class Loopeable {
public:
  Loopeable() = default;

  virtual ~Loopeable() {}

  PURE_VIRTUAL(void render());

  MTHD_VIRTUAL(void update(f32_t dt)) {}
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_LOOPEABLE_HPP
