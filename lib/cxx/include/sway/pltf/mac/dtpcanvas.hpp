#ifndef SWAY_PLTF_MAC_DTPCANVAS_HPP
#define SWAY_PLTF_MAC_DTPCANVAS_HPP

#include <sway/core.hpp>
#include <sway/pltf/mac/dtpcontext.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/pltf/mac/dtpvisualattributes.hpp>
#include <sway/pltf/mac/dtpwindow.hpp>
#include <sway/pltf/prereqs.hpp>
#include <sway/pltf/typedefs.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

class DTPCanvas : public DTPWindow {
  DECLARE_CLASS_POINTER_ALIASES(DTPCanvas)

public:
  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] connection Экранное соедининение с сервером.
   * @param[in] windowInfo Начальные параметры окна.
   */
  DTPCanvas(DTPScreenConnection::SharedPtr_t connection, const WindowInitialInfo &windowInfo);

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  ~DTPCanvas() = default;

  /**
   * @brief Получает контекст.
   */
  auto getContext() -> Context::SharedPtr_t { return context_; }

  MTHD_OVERRIDE(void handleCreateNotifyEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleConfigureNotifyEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleExposeEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleFocusInEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleFocusOutEvent(const XEvent &event)) {}

private:
  auto chooseBestSuitable_(
      DTPScreenConnection::SharedPtr_t connection, GLXFBConfig *configs, i32_t numConfigs) -> GLXFBConfig;

  auto getMultisampleAttributes_(
      DTPScreenConnection::SharedPtr_t connection, GLXFBConfig config) -> DTPVisualAttributes;

  Context::SharedPtr_t context_;  // Контекст поверхности холста.
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_MAC_DTPCANVAS_HPP
