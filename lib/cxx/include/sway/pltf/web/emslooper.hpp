#ifndef SWAY_PLTF_WEB_EMSLOOPER_HPP
#define SWAY_PLTF_WEB_EMSLOOPER_HPP

#include <sway/core.hpp>
#include <sway/pltf/loopeable.hpp>
#include <sway/pltf/looper.hpp>
#include <sway/pltf/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class EMSLooper : public Looper {
public:
  EMSLooper();

  DTOR_VIRTUAL_DEFAULT(EMSLooper);

  MTHD_OVERRIDE(void setLoopeable(Loopeable::SharedPtr_t loopeable)) { loopeable_ = loopeable; }

  MTHD_OVERRIDE(auto loop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool);

  MTHD_OVERRIDE(void stop());

  MTHD_OVERRIDE(void pause());

  MTHD_OVERRIDE(void resume());

private:
  Loopeable::SharedPtr_t loopeable_;
  bool running_;
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_WEB_EMSLOOPER_HPP
