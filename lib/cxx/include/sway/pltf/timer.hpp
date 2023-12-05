#ifndef SWAY_PLTF_TIMER_HPP
#define SWAY_PLTF_TIMER_HPP

#include <sway/core.hpp>

#ifdef EMSCRIPTEN_PLATFORM
#  include <emscripten.h>
#else
#  include <chrono>  // std::chrono
using namespace std::chrono;
#endif

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class Timer {
public:
  Timer() {
#ifdef EMSCRIPTEN_PLATFORM
    prev_ = emscripten_get_now();
#else
    prev_ = high_resolution_clock::now();
#endif
  }

  ~Timer() = default;

  auto started() -> f32_t {
#ifdef EMSCRIPTEN_PLATFORM
    curr_ = emscripten_get_now();
    return static_cast<f32_t>(curr_ - prev_) / 1000.0F;
#else
    curr_ = high_resolution_clock::now();
    return duration<f32_t, seconds::period>(curr_ - prev_).count();
#endif
  }

  void ended() { prev_ = curr_; }

private:
#ifdef EMSCRIPTEN_PLATFORM
  f64_t prev_;
  f64_t curr_;
#else
  steady_clock::time_point prev_;
  steady_clock::time_point curr_;
#endif
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_TIMER_HPP
