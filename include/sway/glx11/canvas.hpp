#ifndef SWAY_GLX11_CANVAS_HPP
#define SWAY_GLX11_CANVAS_HPP

#include <sway/glx11/glxcontext.hpp>
#include <sway/glx11/glxvisualattributes.hpp>
#include <sway/glx11/prereqs.hpp>
#include <sway/glx11/typedefs.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/glx11/xwindow.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class Canvas : public XWindow {
public:
  /*!
   * \brief
   *    Конструктор класса.
   *
   *    Выполняет инициализацию нового экземпляра класса.
   *
   * \param[in] connection
   *    Экранное соедининение с сервером.
   *
   * \param[in] windowInfo
   *    Начальные параметры окна.
   */
  Canvas(XScreenConnectionRef_t connection, const WindowInitialInfo &windowInfo);

  /*!
   * \brief
   *    Деструктор класса.
   *
   *    Освобождает захваченные ресурсы.
   */
  ~Canvas();

  /*!
   * \brief
   *    Получает контекст.
   */
  GlxContextRef_t getContext();

  virtual void handleCreateNotifyEvent(const XEvent &event) override;
  virtual void handleConfigureNotifyEvent(const XEvent &event) override;
  virtual void handleExposeEvent(const XEvent &event) override;
  virtual void handleFocusInEvent(const XEvent &event) override;
  virtual void handleFocusOutEvent(const XEvent &event) override;

private:
  GLXFBConfig _chooseBestSuitable(XScreenConnectionRef_t connection, GLXFBConfig *configs, s32_t numConfigs);

  GlxVisualAttributes _getMultisampleAttributes(XScreenConnectionRef_t connection, GLXFBConfig config);

private:
  GlxContextRef_t _context; /*!< Контекст поверхности холста. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif
