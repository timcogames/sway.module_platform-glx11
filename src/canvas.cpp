#include <sway/core.hpp>
#include <sway/glx11/canvas.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

static s32_t fbAttributes[] = {GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT, GLX_RED_SIZE, 1,
    GLX_GREEN_SIZE, 1, GLX_BLUE_SIZE, 1, GLX_ALPHA_SIZE, 0, GLX_DEPTH_SIZE, 0, GLX_STENCIL_SIZE, 0, GLX_CONFIG_CAVEAT,
    GLX_NONE, GLX_DOUBLEBUFFER, true, 0};

Canvas::Canvas(XScreenConnectionRef_t connection, const WindowInitialInfo &windowInfo)
    : XWindow(connection) {
  s32_t numConfigs;
  GLXFBConfig *configs, config;
  configs = glXChooseFBConfig(connection->getDisplay(), connection->getScreenNumber(), fbAttributes, &numConfigs);
  if (configs && (numConfigs > 0)) {
    config = _chooseBestSuitable(connection, configs, numConfigs);
    XFree(configs);
  }

  createDummy(glXGetVisualFromFBConfig(connection->getDisplay(), config), windowInfo);
  setSizeHints(windowInfo.size, windowInfo.resizable);
  setTitle(core::misc::format("Sway // %s", windowInfo.title).c_str());
  setPosition(windowInfo.fullscreen ? 0 : (connection->getDisplaySize().getW() - windowInfo.size.normal.getW()) / 2,
      windowInfo.fullscreen ? 0 : (connection->getDisplaySize().getH() - windowInfo.size.normal.getH()) / 2);

  _context = std::make_shared<GlxContext>(connection, (XWindow *)this);
  _context->createLegacy(config);
}

Canvas::~Canvas() {
  // Empty
}

void Canvas::handleCreateNotifyEvent(const XEvent &event) {
  // Empty
}

void Canvas::handleConfigureNotifyEvent(const XEvent &event) {
  // Empty
}

void Canvas::handleExposeEvent(const XEvent &event) {
  // Empty
}

void Canvas::handleFocusInEvent(const XEvent &event) {
  // Empty
}

void Canvas::handleFocusOutEvent(const XEvent &event) {
  // Empty
}

GlxContextRef_t Canvas::getContext() { return _context; }

GLXFBConfig Canvas::_chooseBestSuitable(XScreenConnectionRef_t connection, GLXFBConfig *configs, s32_t numConfigs) {
  s32_t bestScore = DONT_CARE, bestNumSamples = DONT_CARE;

  for (s32_t i = 0; i < numConfigs; ++i) {
    GlxVisualAttributes attrs = _getMultisampleAttributes(connection, configs[i]);
    if (bestScore < 0 || (attrs.numMultisample && (attrs.numSamples > bestNumSamples))) {
      bestScore = i;
      bestNumSamples = attrs.numSamples;
    }
  }

  return configs[bestScore];
}

GlxVisualAttributes Canvas::_getMultisampleAttributes(XScreenConnectionRef_t connection, GLXFBConfig config) {
  lpcstr_t extensions = glXQueryExtensionsString(connection->getDisplay(), connection->getScreenNumber());
  GlxVisualAttributes attrs;

  if (extensions && strstr(extensions, "GLX_ARB_multisample")) {
    glXGetFBConfigAttrib(connection->getDisplay(), config, GLX_SAMPLE_BUFFERS_ARB, &attrs.numMultisample);
    glXGetFBConfigAttrib(connection->getDisplay(), config, GLX_SAMPLES_ARB, &attrs.numSamples);
  } else {
    attrs.numMultisample = 0;
    attrs.numSamples = 0;
  }

  return attrs;
}

NAMESPACE_END(glx11)
NAMESPACE_END(sway)
