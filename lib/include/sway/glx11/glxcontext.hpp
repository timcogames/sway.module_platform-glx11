#ifndef SWAY_GLX11_GLXCONTEXT_HPP
#define SWAY_GLX11_GLXCONTEXT_HPP

#include <sway/glx11/prereqs.hpp>
#include <sway/glx11/typedefs.hpp>
#include <sway/glx11/xscreenconnection.hpp>
#include <sway/glx11/xwindow.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/**
 * @brief Контекст поверхности холста.
 *
 */
class GlxContext {
public:
  /**
   * @brief Конструктор класса.
   * Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] connection Экранное соедининение с сервером.
   * @param[in] window Окно графического интерфейса.
   *
   */
  GlxContext(XScreenConnectionRef_t connection, XWindow *window);

  /**
   * @brief Деструктор класса.
   * Уничтожает контекст визуализации.
   *
   */
  ~GlxContext();

  /**
   * @brief Создает контекст визуализации.
   *
   */
  void createLegacy(GLXFBConfig fbconfig);

  /**
   * @brief Прикрепляет контекст к окну.
   *
   * @sa doneCurrent()
   *
   */
  bool makeCurrent();

  /**
   * @brief Освобождаем контекст.
   *
   * @sa makeCurrent()
   *
   */
  bool doneCurrent();

  /**
   * @brief Обмен буферов.
   *
   */
  void present();

private:
  GLXContext _context;
  GLXDrawable _drawable;
  XScreenConnectionRef_t _connection; /*!< Экранное соедининение с сервером. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif
