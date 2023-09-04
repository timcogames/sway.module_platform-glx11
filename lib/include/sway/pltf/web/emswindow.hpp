#ifndef SWAY_PLTF_WEB_EMSWINDOW_HPP
#define SWAY_PLTF_WEB_EMSWINDOW_HPP

#include <sway/core.hpp>
#include <sway/pltf/context.hpp>
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

enum class WindowEventType {
  SIZE_CHANGE,
  RESOLUTION_CHANGE,
  FULLSCREEN_CHANGE,
  SCREEN_CHANGE,
  FOCUS_CHANGE,
  CLOSE,
  SHOW,
  HIDE,
  MINIMIZE,
  MAXIMIZE,
  RESTORE
};

class EMSWindow {
public:
  using CallbackFunc_t = void (*)(void *);

  EMSWindow(std::shared_ptr<Context> context);

  ~EMSWindow() = default;

  auto eventLoop(CallbackFunc_t func, void *arg, [[maybe_unused]] bool keepgoing) -> bool;

  /**
   * @brief Устанавливает размер окна.
   *
   * @param[in] w Ширина окна.
   * @param[in] h Высота окна.
   */
  void setSize(s32_t w, s32_t h);

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

  void handleResize() {
    Event sizeChangeEvent{WindowEventType::SIZE_CHANGE};
    sizeChangeEvent.size = math::size2i_t(0, 0);
    sendEvent(sizeChangeEvent);
  }
  // void handleFullscreenChange(bool fullscreen);

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

  void sendEvent(const EMSWindow::Event &event) {
    std::unique_lock lock{eventQueueMutex_};
    eventQueue_.push(event);
    lock.unlock();
    eventQueueCondition_.notify_all();
  }

  std::queue<EMSWindow::Event> getEvents(bool waitForEvents) {
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
