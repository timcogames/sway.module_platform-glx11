#ifndef SWAY_PLTF_TIMER_HPP
#define SWAY_PLTF_TIMER_HPP

#include <sway/core.hpp>
#include <sway/pltf/_stdafx.hpp>

namespace sway::pltf {

class Timer {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Timer() {
#ifdef EMSCRIPTEN_PLATFORM
    prev_ = emscripten_get_now();
#else
    prev_ = high_resolution_clock::now();
#endif
  }

  ~Timer() = default;

  /** @} */
#pragma endregion

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

}  // namespace sway::pltf

#endif  // SWAY_PLTF_TIMER_HPP
