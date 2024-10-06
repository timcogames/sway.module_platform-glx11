#ifndef SWAY_PLTF_WEB_EMSWINDOW_HPP
#define SWAY_PLTF_WEB_EMSWINDOW_HPP

#include <sway/core.hpp>
#include <sway/pltf/context.hpp>
#include <sway/pltf/typedefs.hpp>
#include <sway/pltf/windoweventtypes.hpp>
#include <sway/pltf/windowinitialinfo.hpp>
#include <sway/pltf/windowmodes.hpp>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

struct SizeChangedEventData : public core::foundation::EventData {
  math::size2i_t size;

  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) { return ""; }  // clang-format on

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

class EMSWindow {
  DECLARE_EVENT(EVT_SIZE_CHANGED, SizeChanged);

public:
  using CallbackFunc_t = void (*)(void *);

  EMSWindow(Context::SharedPtr_t ctx);

  ~EMSWindow() = default;

  /**
   * @brief Устанавливает размер окна.
   *
   * @param[in] wdt Ширина окна.
   * @param[in] hgt Высота окна.
   */
  void setSize(i32_t wdt, i32_t hgt);

  /**
   * @brief Получает размер окна.
   */
  [[nodiscard]] auto getSize() const -> math::size2i_t;

  /**
   * @brief Переключает в полноэкранный / оконный режим.
   *
   * @param[in] fullscreen Включить полноэкранный режим?
   */
  void setFullscreen(bool fullscreen);

  void sendEvent(core::foundation::Event::Ptr_t evt);

  void handleResize();

  auto getEvents(bool waitForEvents) -> std::queue<core::foundation::Event::Ptr_t>;

private:
  Context::SharedPtr_t context_;

  std::queue<core::foundation::Event *> eventQueue_;
  std::mutex eventQueueMutex_;
  std::condition_variable eventQueueCondition_;
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_WEB_EMSWINDOW_HPP
