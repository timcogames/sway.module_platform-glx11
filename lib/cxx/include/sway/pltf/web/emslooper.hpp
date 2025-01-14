#ifndef SWAY_PLTF_WEB_EMSLOOPER_HPP
#define SWAY_PLTF_WEB_EMSLOOPER_HPP

#include <sway/core.hpp>
#include <sway/pltf/loopeable.hpp>
#include <sway/pltf/looper.hpp>
#include <sway/pltf/typedefs.hpp>

namespace sway::pltf {

class EMSLooper : public Looper {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  EMSLooper();

  virtual ~EMSLooper() = default;

  /** @} */
#pragma endregion

  MTHD_OVERRIDE(void setLoopeable(LoopeableSharedPtr_t loopeable)) { loopeable_ = loopeable; }

  MTHD_OVERRIDE(auto loop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool);

  MTHD_OVERRIDE(void stop());

  MTHD_OVERRIDE(void pause());

  MTHD_OVERRIDE(void resume());

private:
  LoopeableSharedPtr_t loopeable_;
  bool running_;
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WEB_EMSLOOPER_HPP
