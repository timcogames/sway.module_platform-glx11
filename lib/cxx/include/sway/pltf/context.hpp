#ifndef SWAY_PLTF_CONTEXT_HPP
#define SWAY_PLTF_CONTEXT_HPP

#include <sway/core.hpp>
#include <sway/pltf/typedefs.hpp>

namespace sway::pltf {

class Context {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  virtual ~Context() = default;

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"

  PURE_VIRTUAL(void create(void *arg));

  PURE_VIRTUAL(void destroy());

  PURE_VIRTUAL(auto makeCurrent() -> bool);

  PURE_VIRTUAL(auto doneCurrent() -> bool);

  PURE_VIRTUAL(void present());

#pragma endregion
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_CONTEXT_HPP
