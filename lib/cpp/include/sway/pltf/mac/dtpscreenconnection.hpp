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
  auto getDisplay() const -> Display *;

  /**
   * @brief Получает номер экрана.
   */
  auto getScreenNumber() const -> s32_t;

  /**
   * @brief Получает корневое окно.
   */
  auto getRootWindow() const -> Window;

  /**
   * @brief Получает размер дисплея.
   */
  auto getDisplaySize() const -> math::size2i_t;

private:
  Display *display_;  // Указатель на структуру дисплея.
  s32_t screen_;  // Номер экрана.
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
