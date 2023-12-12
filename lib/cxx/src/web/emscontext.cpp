#include <sway/pltf/web/emscontext.hpp>

#include <cassert>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

EMSContext::EMSContext(const std::string &canvasId)
    : canvasId_(canvasId) {}

EMSContext::~EMSContext() {
  if (!doneCurrent()) {
    printf("Failed to deactivate shared context before sharing.\n");
  }
}

void EMSContext::create([[maybe_unused]] void *arg) {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.depth = attrs.stencil = attrs.antialias = 1;
  attrs.alpha = 0;
  attrs.explicitSwapControl = 1;
  attrs.majorVersion = 2;  // WebGL 2.0
  attrs.minorVersion = 0;
  attrs.enableExtensionsByDefault = 1;
  context_ = emscripten_webgl_create_context(canvasId_.c_str(), &attrs);
  if (context_ <= 0) {
    if (context_ == EMSCRIPTEN_RESULT_UNKNOWN_TARGET) {
      std::fprintf(stderr, "[EMSContext] Cannot create context, unknown target supplied: %c\n", canvasId_.c_str());
    } else {
      std::fprintf(stderr, "[EMSContext] WebGL2 context could not be created: %i\n", context_);
    }
  }
}

void EMSContext::destroy() {
  if (context_ <= 0) {
    return;
  }

  emscripten_webgl_make_context_current(0);
  emscripten_webgl_destroy_context(context_);
  context_ = 0;
}

auto EMSContext::makeCurrent() -> bool {
  return emscripten_webgl_make_context_current(context_) == EMSCRIPTEN_RESULT_SUCCESS;
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
