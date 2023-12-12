#include <sway/pltf/mac/dtpcontext.hpp>

#include <cassert>
#include <iostream>
#include <stdio.h>
#include <string.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

DTPContext::DTPContext(DTPScreenConnectionRef_t connection, DTPWindow *window)
    : connection_(connection)
    , drawable_(window->getWindowHandle()) {}

DTPContext::~DTPContext() {
  if (!doneCurrent()) {
    printf("Failed to deactivate shared context before sharing.\n");
  }
}

void DTPContext::create(void *arg) {
  context_ = glXCreateNewContext(connection_->getDisplay(), (GLXFBConfig)arg, GLX_RGBA_TYPE, nullptr, True);
  if (context_ == nullptr) {
    throw core::runtime::Exception("Couldn't create GLX context.");
  }

  if (glXIsDirect(connection_->getDisplay(), context_) == 0) {
    printf("Unable to create direct rendering context.\n");
  }
}

void DTPContext::destroy() { glXDestroyContext(connection_->getDisplay(), context_); }

auto DTPContext::makeCurrent() -> bool {
  if (glXGetCurrentContext() != context_) {
    return glXMakeCurrent(connection_->getDisplay(), drawable_, context_);
  }

  return false;
}

auto DTPContext::doneCurrent() -> bool { return glXMakeCurrent(connection_->getDisplay(), None, nullptr); }

void DTPContext::present() { glXSwapBuffers(connection_->getDisplay(), drawable_); }

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
