#include <sway/pltf/web/emscontext.hpp>

#include <cassert>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

EMSContext::EMSContext()
    : targetId_("#canvas") {}

EMSContext::~EMSContext() {
  if (!doneCurrent()) {
    printf("Failed to deactivate shared context before sharing.\n");
  }
}

void EMSContext::create([[maybe_unused]] void *config) {
  EmscriptenWebGLContextAttributes attrs;
  emscripten_webgl_init_context_attributes(&attrs);
  attrs.depth = 1;
  attrs.stencil = 1;
  attrs.antialias = 1;
  attrs.majorVersion = 2;  // WebGL 2.0
  attrs.minorVersion = 0;
  attrs.enableExtensionsByDefault = 1;
  context_ = emscripten_webgl_create_context(targetId_.c_str(), &attrs);
  if (context_ <= 0) {
    if (context_ == EMSCRIPTEN_RESULT_UNKNOWN_TARGET) {
    }

    printf("Webgl ctx could not be created!\n");
  }
}

auto EMSContext::makeCurrent() -> bool {
  return emscripten_webgl_make_context_current(context_) == EMSCRIPTEN_RESULT_SUCCESS;
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
