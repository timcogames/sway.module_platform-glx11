#include <sway/pltf/web/emscontext.hpp>
#include <sway/pltf/web/emswindow.hpp>

#include <emscripten.h>
#include <emscripten/html5.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

EMSWindow::EMSWindow(std::shared_ptr<Context> context)
    : context_(context) {}

auto EMSWindow::eventLoop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool {
  emscripten_set_main_loop_arg(func, arg, 0, 1);
  return true;
}

void EMSWindow::setSize(s32_t w, s32_t h) {
  auto ctx = std::static_pointer_cast<EMSContext>(context_);

  emscripten_set_canvas_element_size(ctx->getTargetId().c_str(), w, h);
}

auto EMSWindow::getSize() const -> math::size2i_t {
  auto ctx = std::static_pointer_cast<EMSContext>(context_);

  auto elementWt = 0.0;
  auto elementHt = 0.0;
  emscripten_get_element_css_size(ctx->getTargetId().c_str(), &elementWt, &elementHt);

  return {(s32_t)elementWt, (s32_t)elementHt};
}

EM_BOOL onCanvasResizeCallback(int type, const void *, void *userData) {
  if (type == EMSCRIPTEN_EVENT_CANVASRESIZED) {
    const auto nativeWindow = static_cast<EMSWindow *>(userData);
    nativeWindow->handleResize();
    return EM_TRUE;
  }

  return EM_FALSE;
}

void EMSWindow::setFullscreen(bool fullscreen) {
  auto ctx = std::static_pointer_cast<EMSContext>(context_);
  auto highDpi = true;

  EmscriptenFullscreenChangeEvent status = {0};
  EMSCRIPTEN_RESULT result = emscripten_get_fullscreen_status(&status);
  if (result == EMSCRIPTEN_RESULT_SUCCESS) {
    if (fullscreen) {
      EmscriptenFullscreenStrategy fullscreenStrategy;
      fullscreenStrategy.scaleMode = EMSCRIPTEN_FULLSCREEN_SCALE_STRETCH;
      fullscreenStrategy.canvasResolutionScaleMode =
          highDpi ? EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_HIDEF : EMSCRIPTEN_FULLSCREEN_CANVAS_SCALE_STDDEF;
      fullscreenStrategy.filteringMode =
          EMSCRIPTEN_FULLSCREEN_FILTERING_DEFAULT;  // EMSCRIPTEN_FULLSCREEN_FILTERING_NEAREST;
      fullscreenStrategy.canvasResizedCallback = onCanvasResizeCallback;
      fullscreenStrategy.canvasResizedCallbackUserData = this;

      result = emscripten_request_fullscreen_strategy(ctx->getTargetId().c_str(), EM_TRUE, &fullscreenStrategy);
    } else {
      result = emscripten_exit_fullscreen();
    }
  }
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
