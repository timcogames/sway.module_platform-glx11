#ifndef SWAY_PLTF_MAC_DTPCANVAS_HPP
#define SWAY_PLTF_MAC_DTPCANVAS_HPP

#include <sway/core.hpp>
#include <sway/pltf/mac/dtpcontext.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/pltf/mac/dtpvisualattributes.hpp>
#include <sway/pltf/mac/dtpwindow.hpp>
#include <sway/pltf/prereqs.hpp>
#include <sway/pltf/typedefs.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class DTPCanvas : public DTPWindow {
public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] connection Экранное соедининение с сервером.
   * @param[in] windowInfo Начальные параметры окна.
   */
  DTPCanvas(DTPScreenConnectionRef_t connection, const WindowInitialInfo &windowInfo);

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  ~DTPCanvas() = default;

  /**
   * @brief Получает контекст.
   */
  auto getContext() -> std::shared_ptr<Context> { return context_; }

  MTHD_OVERRIDE(void handleCreateNotifyEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleConfigureNotifyEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleExposeEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleFocusInEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleFocusOutEvent(const XEvent &event)) {}

private:
  auto chooseBestSuitable_(DTPScreenConnectionRef_t connection, GLXFBConfig *configs, s32_t numConfigs) -> GLXFBConfig;

  auto getMultisampleAttributes_(DTPScreenConnectionRef_t connection, GLXFBConfig config) -> DTPVisualAttributes;

  std::shared_ptr<Context> context_;  // Контекст поверхности холста.
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_MAC_DTPCANVAS_HPP
