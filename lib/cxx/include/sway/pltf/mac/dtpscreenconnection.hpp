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
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  DTPScreenConnection();

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  ~DTPScreenConnection();

  /** @} */
#pragma endregion

  /**
   * @brief Получает указатель на структуру дисплея.
   */
  [[nodiscard]] auto getDisplay() const -> Display *;

  /**
   * @brief Получает номер экрана.
   */
  [[nodiscard]] auto getScreenNumber() const -> i32_t;

  /**
   * @brief Получает корневое окно.
   */
  [[nodiscard]] auto getRootWindow() const -> Window;

  /**
   * @brief Получает размер дисплея.
   */
  [[nodiscard]] auto getDisplaySize() const -> math::size2i_t;

private:
  Display *display_;  // Указатель на структуру дисплея.
  i32_t screen_;  // Номер экрана.
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
