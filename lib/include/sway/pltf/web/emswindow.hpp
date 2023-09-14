#ifndef SWAY_PLTF_WEB_EMSWINDOW_HPP
#define SWAY_PLTF_WEB_EMSWINDOW_HPP

#include <sway/core.hpp>
#include <sway/pltf/context.hpp>
#include <sway/pltf/windoweventtypes.hpp>
#include <sway/pltf/windowinitialinfo.hpp>
#include <sway/pltf/windowmodes.hpp>

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

struct SizeChangedEventData : public core::foundation::EventData {
  math::size2i_t size;

  // clang-format off
  MTHD_OVERRIDE(auto serialize() const -> std::string) {  // clang-format on
    return "";
  }

  MTHD_OVERRIDE(void deserialize(const std::string &jdata)) {}
};

class EMSWindow {
  DECLARE_EVENT(EVT_SIZE_CHANGED, SizeChanged);

public:
  using CallbackFunc_t = void (*)(void *);

  EMSWindow(std::shared_ptr<Context> ctx);

  ~EMSWindow() = default;

  auto eventLoop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool;

  /**
   * @brief Устанавливает размер окна.
   *
   * @param[in] wdt Ширина окна.
   * @param[in] hgt Высота окна.
   */
  void setSize(s32_t wdt, s32_t hgt);

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

  void sendEvent(core::foundation::Event *evt);

  void handleResize();

  auto getEvents(bool waitForEvents) -> std::queue<core::foundation::Event *>;

private:
  std::shared_ptr<Context> context_;

  std::queue<core::foundation::Event *> eventQueue_;
  std::mutex eventQueueMutex_;
  std::condition_variable eventQueueCondition_;
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WEB_EMSWINDOW_HPP
