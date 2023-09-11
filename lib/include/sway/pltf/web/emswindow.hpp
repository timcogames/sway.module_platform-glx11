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

class EMSWindow {
public:
  using CallbackFunc_t = void (*)(void *);

  EMSWindow(std::shared_ptr<Context> context);

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

  class Event final {
  public:
    Event() = default;
    explicit Event(WindowEventType initType) noexcept
        : type{initType} {}

    WindowEventType type;
    math::size2i_t size;

    union {
      bool fullscreen = false;
      std::uintptr_t displayId;
      bool focus;
    };
  };

  void sendEvent(const EMSWindow::Event &evt) {
    std::unique_lock lock{eventQueueMutex_};
    eventQueue_.push(evt);
    lock.unlock();
    eventQueueCondition_.notify_all();
  }

  void handleResize() {
    EMSWindow::Event sizeChangeEvent{WindowEventType::SIZE_CHANGE};
    sizeChangeEvent.size = math::size2i_t(0, 0);
    sendEvent(sizeChangeEvent);
  }

  // void handleFullscreenChange(bool fullscreen);

  auto getEvents(bool waitForEvents) -> std::queue<EMSWindow::Event> {
    std::unique_lock lock{eventQueueMutex_};

    if (waitForEvents) {
      eventQueueCondition_.wait(lock, [this]() noexcept { return !eventQueue_.empty(); });
    }

    auto result = std::move(eventQueue_);
    eventQueue_ = {};
    return result;
  }

  std::queue<EMSWindow::Event> eventQueue_;
  std::mutex eventQueueMutex_;
  std::condition_variable eventQueueCondition_;

private:
  std::shared_ptr<Context> context_;
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WEB_EMSWINDOW_HPP
