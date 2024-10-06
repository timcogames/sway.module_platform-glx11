#ifndef SWAY_PLTF_LOOPER_HPP
#define SWAY_PLTF_LOOPER_HPP

#include <sway/core.hpp>
#include <sway/pltf/loopeable.hpp>
#include <sway/pltf/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class Looper {
public:
  using CallbackFunc_t = void (*)(void *);

  DTOR_VIRTUAL_DEFAULT(Looper);

  PURE_VIRTUAL(void setLoopeable(Loopeable::SharedPtr_t loopeable));

  PURE_VIRTUAL(auto loop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool);

  PURE_VIRTUAL(void stop());

  PURE_VIRTUAL(void pause());

  PURE_VIRTUAL(void resume());
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_LOOPER_HPP
