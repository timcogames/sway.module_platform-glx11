#ifndef SWAY_PLTF_LOOPEABLE_HPP
#define SWAY_PLTF_LOOPEABLE_HPP

#include <sway/core.hpp>
#include <sway/pltf/typedefs.hpp>

namespace sway::pltf {

class Loopeable {
public:
#pragma region "Ctors/Dtor"

  Loopeable() = default;

  virtual ~Loopeable() = default;

#pragma endregion

#pragma region "Pure virtual methods"

  virtual void render() = 0;

#pragma endregion

  MTHD_VIRTUAL(void update(f32_t dt)) {}
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_LOOPEABLE_HPP
