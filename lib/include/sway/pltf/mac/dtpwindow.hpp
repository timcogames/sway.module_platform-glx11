#ifndef SWAY_PLTF_MAC_DTPWINDOW_HPP
#define SWAY_PLTF_MAC_DTPWINDOW_HPP

#include <sway/pltf/mac/dtpatom.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/pltf/prereqs.hpp>
#include <sway/pltf/typedefs.hpp>
#include <sway/pltf/windoweventlistener.hpp>
#include <sway/pltf/windowinitialinfo.hpp>
#include <sway/pltf/windowmodes.hpp>

// #include <X11/Xutil.h>  // XVisualInfo, XSizeHints

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

typedef std::function<void(const XEvent &)> EventCallbackFunc_t;
typedef std::map<s32_t, EventCallbackFunc_t> EventCallbackFuncMap_t;

class DTPWindow : public WindowEventListener {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] connection Экранное соедининение с сервером.
   */
  DTPWindow(DTPScreenConnectionRef_t connection);

  /**
   * @brief Деструктор класса. Уничтожает главное окно приложения.
   */
  ~DTPWindow();

  /**
   * @brief Добавляет привязку функции к оконному событию.
   *
   * @param[in] type Тип события.
   * @param[in] callback Функция вызываемая при возникновении события.
   */
  void addEventBinding(s32_t type, EventCallbackFunc_t callback);

  /**
   * @brief Создает главное окно приложения.
   *
   * @param[in] visualInfo Информация о дисплее.
   * @param[in] windowInfo Начальные параметры окна.
   * @exception std::runtime_error Неудачное создание окна.
   */
  void createDummy(XVisualInfo *visualInfo, const WindowInitialInfo &windowInfo);

  /**
   * @brief Обрабатывает события.
   */
  bool eventLoop(bool keepgoing);

  /**
   * @brief Устанавливает заголовок окна.
   *
   * @param[in] title Заголовок окна.
   */
  void setTitle(lpcstr_t title);

  /**
   * @brief Устанавливает позицию окна.
   *
   * @param[in] x Координата позиции окна по оси X.
   * @param[in] y Координата позиции окна по оси Y.
   */
  void setPosition(s32_t x, s32_t y);

  /**
   * @brief Получает позицию окна.
   */
  auto getPosition() const -> math::point2i_t;

  /**
   * @brief Устанавливает размер окна.
   *
   * @param[in] w Ширина окна.
   * @param[in] h Высота окна.
   */
  void setSize(s32_t w, s32_t h);

  /**
   * @brief Получает размер окна.
   */
  auto getSize() const -> math::size2i_t;

  /**
   * @brief Устанавливает поведение при смене размера.
   *
   * @param[in] size Размер окна.
   * @param[in] resizable Имеется возможность изменения размера?
   */
  void setSizeHints(const WindowSize &size, bool resizable);

  /**
   * @brief Показывает окно.
   *
   * @sa hide(),
   *     visible()
   */
  void show();

  /**
   * @brief Скрывает окно.
   *
   * @sa show(),
   *     visible()
   *
   */
  void hide();

  /**
   * @brief Получает значение видимости окна.
   *
   * @sa show(),
   *     hide()
   *
   */
  bool visible() const;

  /**
   * @brief Переключает в полноэкранный / оконный режим.
   *
   * @param[in] fullscreen Включить полноэкранный режим?
   */
  void setFullscreen(bool fullscreen);

  /**
   * @brief Устанавливает максимальный размер окна.
   *
   * @param[in] maximized Растянуть окно до максимальных размеров?
   */
  void setMaximize(bool maximized);

  /**
   * @brief Получает идентификатор окна.
   */
  auto getWindowHandle() -> Window { return window_; }

private:
  void initializeAtoms_();

  void initializeEventBindings_();

  /**
   * @brief Устанавливает минимальный размер.
   *
   * @param[out] hints Cтруктура рекомендаций.
   * @param[in] size Размер окна.
   * @param[in] resizable Имеется возможность изменения размера?
   */
  void setMinSize_(XSizeHints *hints, const WindowSize &size, bool resizable);

  /**
   * @brief Устанавливает максимальный размер.
   *
   * @param[out] hints Cтруктура рекомендаций.
   * @param[in] size Размер окна.
   * @param[in] resizable Имеется возможность изменения размера?
   */
  void setMaxSize_(XSizeHints *hints, const WindowSize &size, bool resizable);

private:
  DTPScreenConnectionRef_t connection_;  // Экранное соедининение с сервером.
  Window window_;  // Идентификатор окна.
  Atom wmatom_[kAtom_WMLast], netatom_[kAtom_NetLast];
  EventCallbackFuncMap_t eventCallbacks_;
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_MAC_DTPWINDOW_HPP
