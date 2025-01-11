#ifndef SWAY_PLTF_MAC_DTPCANVAS_HPP
#define SWAY_PLTF_MAC_DTPCANVAS_HPP

#include <sway/core.hpp>
#include <sway/pltf/_stdafx.hpp>
#include <sway/pltf/mac/dtpcontext.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>
#include <sway/pltf/mac/dtpvisualattributes.hpp>
#include <sway/pltf/mac/dtpwindow.hpp>
#include <sway/pltf/typedefs.hpp>

namespace sway::pltf {

class DTPCanvas : public DTPWindow {
public:
#pragma region "Ctors/Dtor"

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   *
   * @param[in] connection Экранное соедининение с сервером.
   * @param[in] windowInfo Начальные параметры окна.
   */
  DTPCanvas(typedefs::DTPScreenConnectionSharedPtr_t connection, const WindowInitialInfo &windowInfo);

  /**
   * @brief Деструктор класса. Освобождает захваченные ресурсы.
   */
  ~DTPCanvas() = default;

#pragma endregion

  /**
   * @brief Получает контекст.
   */
  auto getContext() -> typedefs::ContextSharedPtr_t { return context_; }

  MTHD_OVERRIDE(void handleCreateNotifyEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleConfigureNotifyEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleExposeEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleFocusInEvent(const XEvent &event)) {}

  MTHD_OVERRIDE(void handleFocusOutEvent(const XEvent &event)) {}

private:
  auto chooseBestSuitable_(typedefs::DTPScreenConnectionSharedPtr_t connection, GLXFBConfig *configs, i32_t numConfigs)
      -> GLXFBConfig;

  auto getMultisampleAttributes_(typedefs::DTPScreenConnectionSharedPtr_t connection, GLXFBConfig config)
      -> DTPVisualAttributes;

  typedefs::ContextSharedPtr_t context_;  // Контекст поверхности холста.
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_MAC_DTPCANVAS_HPP
