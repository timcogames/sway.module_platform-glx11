#ifndef SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
#define SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP

#include <sway/pltf/_stdafx.hpp>
#include <sway/pltf/typedefs.hpp>

namespace sway::pltf {

class DTPScreenConnection {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  /**
   * @brief \~russian Конструктор класса. Выполняет инициализацию нового экземпляра класса.
   */
  DTPScreenConnection();

  /**
   * @brief \~russian Деструктор класса. Освобождает захваченные ресурсы.
   */
  ~DTPScreenConnection();

  /** @} */
#pragma endregion

  /**
   * @brief \~russian Получает указатель на структуру дисплея.
   */
  [[nodiscard]] auto getDisplay() const -> Display *;

  /**
   * @brief \~russian Получает номер экрана.
   */
  [[nodiscard]] auto getScreenNumber() const -> i32_t;

  /**
   * @brief \~russian Получает корневое окно.
   */
  [[nodiscard]] auto getRootWindow() const -> Window;

  /**
   * @brief \~russian Получает размер дисплея.
   */
  [[nodiscard]] auto getDisplaySize() const -> math::size2i_t;

private:
  Display *display_;  //!< \~russian Указатель на структуру дисплея.
  i32_t screen_;  //!< \~russian Номер экрана.
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
