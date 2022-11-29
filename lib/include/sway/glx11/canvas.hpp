#ifndef SWAY_GLX11_CANVAS_HPP
#define SWAY_GLX11_CANVAS_HPP

#include <sway/glx11/glxcontext.hpp>
#include <sway/glx11/glxvisualattributes.hpp>
#include <sway/glx11/prereqs.hpp>
#include <sway/glx11/typedefs.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/glx11/xwindow.hpp>
#include <sway/keywords.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class Canvas : public XWindow {
public:
  /**
   * @brief Конструктор класса.
   * Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] connection Экранное соедининение с сервером.
   * @param[in] windowInfo Начальные параметры окна.
   *
   */
  Canvas(XScreenConnectionRef_t connection, const WindowInitialInfo &windowInfo);

  /**
   * @brief Деструктор класса.
   * Освобождает захваченные ресурсы.
   *
   */
  ~Canvas();

  /**
   * @brief Получает контекст.
   *
   */
  auto getContext() -> GlxContextRef_t;

  MTHD_OVERRIDE(void handleCreateNotifyEvent(const XEvent &event));

  MTHD_OVERRIDE(void handleConfigureNotifyEvent(const XEvent &event));

  MTHD_OVERRIDE(void handleExposeEvent(const XEvent &event));

  MTHD_OVERRIDE(void handleFocusInEvent(const XEvent &event));

  MTHD_OVERRIDE(void handleFocusOutEvent(const XEvent &event));

private:
  auto chooseBestSuitable_(XScreenConnectionRef_t connection, GLXFBConfig *configs, s32_t numConfigs) -> GLXFBConfig;

  auto getMultisampleAttributes_(XScreenConnectionRef_t connection, GLXFBConfig config) -> GlxVisualAttributes;

  GlxContextRef_t _context; /*!< Контекст поверхности холста. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif  // SWAY_GLX11_CANVAS_HPP
