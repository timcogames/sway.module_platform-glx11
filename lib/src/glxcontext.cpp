#include <sway/glx11/glxcontext.hpp>

#include <cassert>
#include <iostream>
#include <stdio.h>
#include <string.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

GlxContext::GlxContext(XScreenConnectionRef_t connection, XWindow *window)
    : connection_(connection)
    , drawable_(window->getWindowHandle()) {
  // Empty
}

GlxContext::~GlxContext() {
  if (!doneCurrent())
    printf("Failed to deactivate shared context before sharing.\n");

  glXDestroyContext(connection_->getDisplay(), context_);
}

void GlxContext::createLegacy(GLXFBConfig fbconfig) {
  context_ = glXCreateNewContext(connection_->getDisplay(), fbconfig, GLX_RGBA_TYPE, 0, True);
  if (!context_) {
    throw core::runtime::Exception("Couldn't create GLX context.");
  }

  if (!glXIsDirect(connection_->getDisplay(), context_)) {
    printf("Unable to create direct rendering context.\n");
  }
}

auto GlxContext::makeCurrent() -> bool {
  if (glXGetCurrentContext() != context_) {
    return glXMakeCurrent(connection_->getDisplay(), drawable_, context_);
  }

  return false;
}

auto GlxContext::doneCurrent() -> bool { return glXMakeCurrent(connection_->getDisplay(), None, NULL); }

void GlxContext::present() { glXSwapBuffers(connection_->getDisplay(), drawable_); }

NAMESPACE_END(glx11)
NAMESPACE_END(sway)
