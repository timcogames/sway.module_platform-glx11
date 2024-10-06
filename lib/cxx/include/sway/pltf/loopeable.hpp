#ifndef SWAY_PLTF_LOOPEABLE_HPP
#define SWAY_PLTF_LOOPEABLE_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class Loopeable {
  DECLARE_CLASS_POINTER_ALIASES(Loopeable)

public:
  Loopeable() = default;

  virtual ~Loopeable() {}

  PURE_VIRTUAL(void render());

  MTHD_VIRTUAL(void update(f32_t dt)) {}
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_LOOPEABLE_HPP
