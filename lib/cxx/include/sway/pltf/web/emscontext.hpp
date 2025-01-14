#ifndef SWAY_PLTF_WEB_EMSCONTEXT_HPP
#define SWAY_PLTF_WEB_EMSCONTEXT_HPP

#include <sway/core.hpp>
#include <sway/pltf/_stdafx.hpp>
#include <sway/pltf/context.hpp>

namespace sway::pltf {

class EMSContext : public Context {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  EMSContext(const std::string &canvasId);

  virtual ~EMSContext();

  /** @} */
#pragma endregion

  MTHD_OVERRIDE(void create(void *arg));

  MTHD_OVERRIDE(void destroy());

  /**
   * @brief \~russian Прикрепляет контекст к окну.
   *
   * @sa doneCurrent()
   */

  MTHD_OVERRIDE(auto makeCurrent() -> bool);

  /**
   * @brief \~russian Освобождаем контекст.
   *
   * @sa makeCurrent()
   */
  MTHD_OVERRIDE(auto doneCurrent() -> bool) {
    return true;
  }

  /**
   * @brief \~russian Обмен буферов.
   */
  MTHD_OVERRIDE(void present()) {}

  [[nodiscard]] auto getCanvasId() const -> std::string { return canvasId_; }

private:
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context_;
  std::string canvasId_;
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WEB_EMSCONTEXT_HPP
