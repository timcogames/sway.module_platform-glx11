#ifndef SWAY_PLTF_MAC_DTPWINDOW_HPP
#define SWAY_PLTF_MAC_DTPWINDOW_HPP

#include <sway/core.hpp>
#include <sway/pltf/_stdafx.hpp>
#include <sway/pltf/mac/dtpatom.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/pltf/typedefs.hpp>
#include <sway/pltf/windoweventlistener.hpp>
#include <sway/pltf/windowinitialinfo.hpp>
#include <sway/pltf/windowmodes.hpp>

namespace sway::pltf {

using EventCallbackFunc_t = std::function<void(const XEvent &)>;
using EventCallbackFuncMap_t = std::map<i32_t, EventCallbackFunc_t>;

class DTPWindow : public WindowEventListener {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  /**
   * \~english
   * @brief Constructor class. Performs initialization of a new instance of the class.
   * @param[in] connection Screen connection to the server.
   *
   * \~russian
   * @brief Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   * @param[in] connection Экранное соедининение с сервером.
   */
  DTPWindow(DTPScreenConnectionSharedPtr_t connection);

  /**
   * @brief \~english Destructor. Destroys main application window. \~russian Деструктор класса. Уничтожает главное окно
   * приложения.
   */
  ~DTPWindow();

  /** @} */
#pragma endregion

  /**
   * \~english
   * @brief Adds a function binding to a window event.
   * @param[in] type Event type.
   * @param[in] callback Callback function.
   *
   * \~russian
   * @brief Добавляет привязку функции к оконному событию.
   * @param[in] type Тип события.
   * @param[in] callback Функция вызываемая при возникновении события.
   */
  void addEventBinding(i32_t type, EventCallbackFunc_t callback);

  /**
   * \~english
   * @brief Creates the main application window.
   * @param[in] visualInfo Display information.
   * @param[in] windowInfo Initial window parameters.
   * @exception std::runtime_error Window creation failure.
   *
   * \~russian
   * @brief Создает главное окно приложения.
   * @param[in] visualInfo Информация о дисплее.
   * @param[in] windowInfo Начальные параметры окна.
   * @exception std::runtime_error Неудачное создание окна.
   */
  void createDummy(XVisualInfo *visualInfo, const WindowInitialInfo &windowInfo);

  /**
   * @brief \~english Handles events. \~russian Обрабатывает события.
   */
  auto eventLoop(bool keepgoing) -> bool;

  /**
   * \~english
   * @brief Sets the title of the window.
   * @param[in] title Window title.
   *
   * \~russian
   * @brief Устанавливает заголовок окна.
   * @param[in] title Заголовок окна.
   */
  void setTitle(lpcstr_t title);

  /**
   * \~english
   * @brief Sets the position of the window.
   * @param[in] x Coordinate of the window position on the X axis.
   * @param[in] y Coordinate of the window position on the Y axis.
   *
   * \~russian
   * @brief Устанавливает позицию окна.
   * @param[in] x Координата позиции окна по оси X.
   * @param[in] y Координата позиции окна по оси Y.
   */
  void setPosition(i32_t x, i32_t y);

  /**
   * @brief \~english Gets the position of the window. \~russian Получает позицию окна.
   */
  [[nodiscard]] auto getPosition() const -> math::point2i_t;

  /**
   * \~english
   * @brief Sets the size of the window.
   * @param[in] w Width of the window.
   * @param[in] h Height of the window.
   *
   * \~russian
   * @brief Устанавливает размер окна.
   * @param[in] w Ширина окна.
   * @param[in] h Высота окна.
   */
  void setSize(i32_t w, i32_t h);

  /**
   * @brief \~english Gets the size of the window. \~russian Получает размер окна.
   */
  [[nodiscard]] auto getSize() const -> math::size2i_t;

  /**
   * \~english
   * @brief Sets behavior when the size of the window changes.
   * @param[in] size Size of the window.
   * @param[in] resizable Does the window support resizing?
   *
   * \~russian
   * @brief Устанавливает поведение при смене размера.
   * @param[in] size Размер окна.
   * @param[in] resizable Имеется возможность изменения размера?
   */
  void setSizeHints(const WindowSize &size, bool resizable);

  /**
   * @brief \~english Shows the window. \~russian Показывает окно.
   *
   * @sa hide(),
   *     visible()
   */
  void show();

  /**
   * @brief \~english Hides the window. \~russian Скрывает окно.
   *
   * @sa show(),
   *     visible()
   *
   */
  void hide();

  /**
   * @brief \~english Gets the visibility of the window. \~russian Получает значение видимости окна.
   *
   * @sa show(),
   *     hide()
   *
   */
  [[nodiscard]] bool visible() const;

  /**
   * \~english
   * @brief Switches to fullscreen / windowed mode.
   * @param[in] fullscreen Enable fullscreen mode?
   *
   * \~russian
   * @brief Переключает в полноэкранный / оконный режим.
   * @param[in] fullscreen Включить полноэкранный режим?
   */
  void setFullscreen(bool fullscreen);

  /**
   * \~english
   * @brief Sets the maximum size of the window.
   * @param[in] maximized Should the window be maximized?
   *
   * \~russian
   * @brief Устанавливает максимальный размер окна.
   * @param[in] maximized Растянуть окно до максимальных размеров?
   */
  void setMaximize(bool maximized);

  /**
   * @brief \~english Gets the window handle. \~russian Получает идентификатор окна.
   */
  auto getWindowHandle() -> Window { return window_; }

private:
#pragma mark - Private methods

  void initializeAtoms_();

  void initializeEventBindings_();

  /**
   * \~english
   * @brief Sets the minimum size.
   * @param[out] hints Structure of recommendations.
   * @param[in] size Window size.
   * @param[in] resizable Is there a possibility of changing the size?
   *
   * \~russian
   * @brief Устанавливает минимальный размер.
   * @param[out] hints Cтруктура рекомендаций.
   * @param[in] size Размер окна.
   * @param[in] resizable Имеется возможность изменения размера?
   */
  void setMinSize_(XSizeHints *hints, const WindowSize &size, bool resizable);

  /**
   * \~english
   * @brief Sets the maximum size.
   * @param[out] hints Structure of recommendations.
   * @param[in] size Window size.
   * @param[in] resizable Is there a possibility of changing the size?
   *
   * \~russian
   * @brief Устанавливает максимальный размер.
   * @param[out] hints Cтруктура рекомендаций.
   * @param[in] size Размер окна.
   * @param[in] resizable Имеется возможность изменения размера?
   */
  void setMaxSize_(XSizeHints *hints, const WindowSize &size, bool resizable);

#pragma mark - Private variables

  DTPScreenConnectionSharedPtr_t connection_; /*!< \~english Screen connection to the server.
    \~russian Экранное соедининение с сервером. */
  Window window_;  //!< \~english Identifier of the window. \~russian Идентификатор окна.
  Atom wmatom_[kAtom_WMLast], netatom_[kAtom_NetLast];
  EventCallbackFuncMap_t eventCallbacks_;
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_MAC_DTPWINDOW_HPP
