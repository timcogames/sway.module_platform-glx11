#ifndef SWAY_PLTF_LOOPER_HPP
#define SWAY_PLTF_LOOPER_HPP

#include <sway/core.hpp>
#include <sway/pltf/loopeable.hpp>
#include <sway/pltf/typedefs.hpp>

namespace sway::pltf {

class Looper {
public:
  using CallbackFunc_t = void (*)(void *);

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  virtual ~Looper() = default;

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"

  virtual void setLoopeable(LoopeableSharedPtr_t loopeable) = 0;

  virtual auto loop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool = 0;

  virtual void stop() = 0;

  virtual void pause() = 0;

  virtual void resume() = 0;

#pragma endregion
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_LOOPER_HPP
