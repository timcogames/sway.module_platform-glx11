#ifndef SWAY_PLTF_WEB_EMSWINDOW_HPP
#define SWAY_PLTF_WEB_EMSWINDOW_HPP

#include <sway/core.hpp>
#include <sway/pltf/_stdafx.hpp>
#include <sway/pltf/context.hpp>
#include <sway/pltf/typedefs.hpp>
#include <sway/pltf/windoweventtypes.hpp>
#include <sway/pltf/windowinitialinfo.hpp>
#include <sway/pltf/windowmodes.hpp>

namespace sway::pltf {

struct SizeChangedEventData : public core::EventData {
  math::size2i_t size;
};

class EMSWindow {
  DECLARE_EVENT(EVT_SIZE_CHANGED, SizeChanged);

public:
  using CallbackFunc_t = void (*)(void *);

#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  EMSWindow(ContextSharedPtr_t ctx);

  ~EMSWindow() = default;

  /** @} */
#pragma endregion

  /**
   * \~russian
   * @brief Устанавливает размер окна.
   * @param[in] wdt Ширина окна.
   * @param[in] hgt Высота окна.
   */
  void setSize(i32_t wdt, i32_t hgt);

  /**
   * @brief \~russian Получает размер окна.
   */
  [[nodiscard]] auto getSize() const -> math::size2i_t;

  /**
   * \~russian
   * @brief Переключает в полноэкранный / оконный режим.
   * @param[in] fullscreen Включить полноэкранный режим?
   */
  void setFullscreen(bool fullscreen);

  void sendEvent(core::EventTypedefs::Ptr_t evt);

  void handleResize();

  auto getEvents(bool waitForEvents) -> std::queue<core::EventTypedefs::Ptr_t>;

private:
  ContextSharedPtr_t context_;

  std::queue<core::Event *> eventQueue_;
  std::mutex eventQueueMutex_;
  std::condition_variable eventQueueCondition_;
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WEB_EMSWINDOW_HPP
