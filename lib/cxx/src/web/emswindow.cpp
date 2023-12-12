#include <sway/pltf/web/emscontext.hpp>
#include <sway/pltf/web/emswindow.hpp>

#include <emscripten.h>
#include <emscripten/html5.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

auto onCanvasResizeCallback(int eventType, [[maybe_unused]] const void *reserved, void *userData) -> EM_BOOL {
  if (eventType == EMSCRIPTEN_EVENT_CANVASRESIZED) {
    auto *nativeWindow = static_cast<EMSWindow *>(userData);
    nativeWindow->handleResize();
    return EM_TRUE;
  }

  return EM_FALSE;
}

EMSWindow::EMSWindow(std::shared_ptr<Context> ctx)
    : context_(ctx) {}

void EMSWindow::setSize(s32_t wdt, s32_t hgt) {
  auto ctx = std::static_pointer_cast<EMSContext>(context_);

  emscripten_set_canvas_element_size(ctx->getCanvasId().c_str(), wdt, hgt);
}

auto EMSWindow::getSize() const -> math::size2i_t {
  auto ctx = std::static_pointer_cast<EMSContext>(context_);
  auto wdt = 0.0, hgt = 0.0;

  emscripten_get_element_css_size(ctx->getCanvasId().c_str(), &wdt, &hgt);
  return {(s32_t)wdt, (s32_t)hgt};
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

      result = emscripten_request_fullscreen_strategy(ctx->getCanvasId().c_str(), EM_TRUE, &fullscreenStrategy);
    } else {
      result = emscripten_exit_fullscreen();
    }
  }
}

void EMSWindow::sendEvent(core::foundation::Event *evt) {
  std::unique_lock lock{eventQueueMutex_};
  eventQueue_.push(evt);
  lock.unlock();
  eventQueueCondition_.notify_all();
}

void EMSWindow::handleResize() {
  SizeChangedEventData eventData;
  eventData.size = getSize();
  sendEvent(new SizeChangedEvent(0, &eventData));
}

auto EMSWindow::getEvents(bool waitForEvents) -> std::queue<core::foundation::Event *> {
  std::unique_lock lock{eventQueueMutex_};

  if (waitForEvents) {
    eventQueueCondition_.wait(lock, [this]() noexcept { return !eventQueue_.empty(); });
  }

  auto result = std::move(eventQueue_);
  eventQueue_ = {};
  return result;
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
