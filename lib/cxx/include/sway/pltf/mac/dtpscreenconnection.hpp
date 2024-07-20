#ifndef SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
#define SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP

#include <sway/pltf/prereqs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class DTPScreenConnection {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  DTPScreenConnection();

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  ~DTPScreenConnection();

  /**
   * @brief Получает указатель на структуру дисплея.
   */
  [[nodiscard]]
  auto getDisplay() const -> Display *;

  /**
   * @brief Получает номер экрана.
   */
  [[nodiscard]]
  auto getScreenNumber() const -> i32_t;

  /**
   * @brief Получает корневое окно.
   */
  [[nodiscard]]
  auto getRootWindow() const -> Window;

  /**
   * @brief Получает размер дисплея.
   */
  [[nodiscard]]
  auto getDisplaySize() const -> math::size2i_t;

private:
  Display *display_;  // Указатель на структуру дисплея.
  i32_t screen_;  // Номер экрана.
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
