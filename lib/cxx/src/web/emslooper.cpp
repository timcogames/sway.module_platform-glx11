#include <sway/pltf/web/emslooper.hpp>

#ifdef EMSCRIPTEN_PLATFORM
#  include <emscripten.h>
#  include <emscripten/html5.h>
#endif

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

EMSLooper::EMSLooper()
    : running_(false) {}

auto EMSLooper::loop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool {
  running_ = true;

#if EMSCRIPTEN_PLATFORM
  emscripten_set_main_loop_arg(func, arg, 0, 1);
#endif

  return true;
}

void EMSLooper::stop() {
  running_ = false;

#if EMSCRIPTEN_PLATFORM
  emscripten_cancel_main_loop();
#endif
}

void EMSLooper::pause() {
#if EMSCRIPTEN_PLATFORM
  emscripten_pause_main_loop();
#endif
}

void EMSLooper::resume() {
#if EMSCRIPTEN_PLATFORM
  emscripten_resume_main_loop();
#endif
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
