#include <sway/core.hpp>
#include <sway/pltf/mac/dtpcanvas.hpp>

#include <array>
#include <cstring>  // strstr

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

constexpr size_t ATTRIB_LIST_SIZE = 21;
// clang-format off
constexpr std::array<s32_t, ATTRIB_LIST_SIZE> attribList = {
  GLX_RENDER_TYPE, GLX_RGBA_BIT,
  GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
  GLX_RED_SIZE, 1,
  GLX_GREEN_SIZE, 1,
  GLX_BLUE_SIZE, 1,
  GLX_ALPHA_SIZE, 0,
  GLX_DEPTH_SIZE, 0,
  GLX_STENCIL_SIZE, 0,
  GLX_CONFIG_CAVEAT, GLX_NONE,
  GLX_DOUBLEBUFFER, 1,
  None};  // clang-format on

DTPCanvas::DTPCanvas(DTPScreenConnectionRef_t connection, const WindowInitialInfo &windowInfo)
    : DTPWindow(connection) {
  s32_t numConfigs;
  GLXFBConfig *configs, config;
  configs = glXChooseFBConfig(connection->getDisplay(), connection->getScreenNumber(), attribList.data(), &numConfigs);
  if ((configs != nullptr) && (numConfigs > 0)) {
    config = chooseBestSuitable_(connection, configs, numConfigs);
    XFree(configs);
  }

  createDummy(glXGetVisualFromFBConfig(connection->getDisplay(), config), windowInfo);
  setSizeHints(windowInfo.size, windowInfo.resizable);
  setTitle(core::misc::format("Sway // %s", windowInfo.title).c_str());
  setPosition(windowInfo.fullscreen ? 0 : (connection->getDisplaySize().getW() - windowInfo.size.normal.getW()) / 2,
      windowInfo.fullscreen ? 0 : (connection->getDisplaySize().getH() - windowInfo.size.normal.getH()) / 2);

  context_ = std::make_shared<DTPContext>(connection, (DTPWindow *)this);
  context_->create(config);
}

auto DTPCanvas::chooseBestSuitable_(DTPScreenConnectionRef_t connection, GLXFBConfig *configs, s32_t numConfigs)
    -> GLXFBConfig {
  s32_t bestScore = DONT_CARE, bestNumSamples = DONT_CARE;

  for (auto i = 0; i < numConfigs; ++i) {
    auto attrs = getMultisampleAttributes_(connection, configs[i]);
    if (bestScore < 0 || ((attrs.numMultisample != 0) && (attrs.numSamples > bestNumSamples))) {
      bestScore = i;
      bestNumSamples = attrs.numSamples;
    }
  }

  return configs[bestScore];
}

auto DTPCanvas::getMultisampleAttributes_(DTPScreenConnectionRef_t connection, GLXFBConfig config)
    -> DTPVisualAttributes {
  const auto *extensions = glXQueryExtensionsString(connection->getDisplay(), connection->getScreenNumber());
  DTPVisualAttributes attrs;

  if (extensions && std::strstr(extensions, "GLX_ARB_multisample")) {
    glXGetFBConfigAttrib(connection->getDisplay(), config, GLX_SAMPLE_BUFFERS_ARB, &attrs.numMultisample);
    glXGetFBConfigAttrib(connection->getDisplay(), config, GLX_SAMPLES_ARB, &attrs.numSamples);
  } else {
    attrs.numMultisample = 0;
    attrs.numSamples = 0;
  }

  return attrs;
}

NAMESPACE_END(pltf)
NAMESPACE_END(sway)
