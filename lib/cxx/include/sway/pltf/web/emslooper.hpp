#ifndef SWAY_PLTF_WEB_EMSLOOPER_HPP
#define SWAY_PLTF_WEB_EMSLOOPER_HPP

#include <sway/core.hpp>
#include <sway/pltf/loopeable.hpp>
#include <sway/pltf/looper.hpp>

#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class EMSLooper : public Looper {
public:
  EMSLooper();

  DFLT_DTOR_VIRTUAL(EMSLooper);

  MTHD_OVERRIDE(void setLoopeable(std::shared_ptr<Loopeable> loopeable)) { loopeable_ = loopeable; }

  // clang-format off
  MTHD_OVERRIDE(auto loop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool);  // clang-format on

  MTHD_OVERRIDE(void stop());

  MTHD_OVERRIDE(void pause());

  MTHD_OVERRIDE(void resume());

private:
  std::shared_ptr<Loopeable> loopeable_;
  bool running_;
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WEB_EMSLOOPER_HPP
