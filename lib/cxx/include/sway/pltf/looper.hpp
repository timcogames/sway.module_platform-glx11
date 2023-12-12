#ifndef SWAY_PLTF_LOOPER_HPP
#define SWAY_PLTF_LOOPER_HPP

#include <sway/core.hpp>
#include <sway/pltf/loopeable.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class Looper {
public:
  using CallbackFunc_t = void (*)(void *);

  DFLT_DTOR_VIRTUAL(Looper);

  PURE_VIRTUAL(void setLoopeable(std::shared_ptr<Loopeable> loopeable));

  // clang-format off
  PURE_VIRTUAL(auto loop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool);  // clang-format on

  PURE_VIRTUAL(void stop());

  PURE_VIRTUAL(void pause());

  PURE_VIRTUAL(void resume());
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_LOOPER_HPP
