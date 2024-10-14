#ifndef SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
#define SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP

#include <sway/pltf/prereqs.hpp>
#include <sway/pltf/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class DTPScreenConnection {
  DECLARE_PTR_ALIASES(DTPScreenConnection)

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

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_MAC_DTPSCREENCONNECTION_HPP
