#ifndef SWAY_PLTF_CONTEXT_HPP
#define SWAY_PLTF_CONTEXT_HPP

#include <sway/core.hpp>
#include <sway/pltf/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class Context {
  DECLARE_PTR_ALIASES(Context)

public:
#pragma region "Ctors/Dtor"

  DTOR_VIRTUAL_DEFAULT(Context);

#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void create(void *arg));

  PURE_VIRTUAL(void destroy());

  PURE_VIRTUAL(auto makeCurrent() -> bool);

  PURE_VIRTUAL(auto doneCurrent() -> bool);

  PURE_VIRTUAL(void present());

#pragma endregion
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_CONTEXT_HPP
