#ifndef SWAY_PLTF_LOOPEABLE_HPP
#define SWAY_PLTF_LOOPEABLE_HPP

#include <sway/core.hpp>
#include <sway/pltf/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class Loopeable {
  DECLARE_PTR_ALIASES(Loopeable)

public:
#pragma region "Ctors/Dtor"

  Loopeable() = default;

  DTOR_VIRTUAL_DEFAULT(Loopeable);

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void render());

#pragma endregion

  MTHD_VIRTUAL(void update(f32_t dt)) {}
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_LOOPEABLE_HPP
