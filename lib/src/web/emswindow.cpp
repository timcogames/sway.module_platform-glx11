#include <sway/pltf/web/emscontext.hpp>
#include <sway/pltf/web/emswindow.hpp>

#include <emscripten.h>
#include <emscripten/html5.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

EMSWindow::EMSWindow(std::shared_ptr<EMSContext> context)
    : context_(context) {}

auto EMSWindow::eventLoop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool {
  emscripten_set_main_loop_arg(func, arg, 0, 1);
  return true;
}

void EMSWindow::setSize(s32_t w, s32_t h) { emscripten_set_canvas_element_size(context_->getTargetId().c_str(), w, h); }

auto EMSWindow::getSize() const -> math::size2i_t {
  auto elementWt = 0.0;
  auto elementHt = 0.0;
  emscripten_get_element_css_size(context_->getTargetId().c_str(), &elementWt, &elementHt);

  return {(s32_t)elementWt, (s32_t)elementHt};
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
