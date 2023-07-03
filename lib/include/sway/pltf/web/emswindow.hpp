#ifndef SWAY_PLTF_WEB_EMSWINDOW_HPP
#define SWAY_PLTF_WEB_EMSWINDOW_HPP

#include <sway/core.hpp>
#include <sway/pltf/windoweventlistener.hpp>
#include <sway/pltf/windowinitialinfo.hpp>
#include <sway/pltf/windowmodes.hpp>

#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class EMSContext;

class EMSWindow {
public:
  using CallbackFunc_t = void (*)(void *);

  EMSWindow(std::shared_ptr<EMSContext> context);

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

private:
  std::shared_ptr<EMSContext> context_;
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WEB_EMSWINDOW_HPP
