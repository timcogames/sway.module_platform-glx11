#ifndef SWAY_PLTF_WEB_EMSWINDOW_HPP
#define SWAY_PLTF_WEB_EMSWINDOW_HPP

#include <sway/core.hpp>
#include <sway/pltf/windoweventlistener.hpp>
#include <sway/pltf/windowinitialinfo.hpp>
#include <sway/pltf/windowmodes.hpp>

#include <emscripten.h>
#include <emscripten/html5.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class ENSWindow {
public:
  using CallbackFunc_t = void (*)(void *);

  ENSWindow() = default;

  ~ENSWindow() = default;

  auto eventLoop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool {
    emscripten_set_main_loop_arg(func, arg, 0, 1);
    return true;
  }

private:
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WEB_EMSWINDOW_HPP
