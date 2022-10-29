#ifndef SWAY_GLX11_XSCREENCONNECTION_HPP
#define SWAY_GLX11_XSCREENCONNECTION_HPP

#include <sway/glx11/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

class XScreenConnection {
public:
  /*!
   * \brief
   *    Конструктор класса.
   *
   *    Выполняет инициализацию нового экземпляра класса.
   */
  XScreenConnection();

  /*!
   * \brief
   *    Деструктор класса.
   *
   *    Освобождает захваченные ресурсы.
   */
  ~XScreenConnection();

  /*!
   * \brief
   *    Получает указатель на структуру дисплея.
   */
  Display *getDisplay() const;

  /*!
   * \brief
   *    Получает номер экрана.
   */
  s32_t getScreenNumber() const;

  /*!
   * \brief
   *    Получает корневое окно.
   */
  Window getRootWindow() const;

  /*!
   * \brief
   *    Получает размер дисплея.
   */
  math::size2i_t getDisplaySize() const;

private:
  Display *_display; /*!< Указатель на структуру дисплея. */
  s32_t _screen; /*!< Номер экрана. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif
