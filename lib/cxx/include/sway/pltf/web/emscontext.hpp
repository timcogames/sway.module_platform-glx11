#ifndef SWAY_PLTF_WEB_EMSCONTEXT_HPP
#define SWAY_PLTF_WEB_EMSCONTEXT_HPP

#include <sway/core.hpp>
#include <sway/pltf/context.hpp>

#include <emscripten.h>
#include <emscripten/html5.h>
#include <string>

namespace sway::pltf {

class EMSContext : public Context {
public:
  EMSContext(const std::string &canvasId);

  virtual ~EMSContext();

  MTHD_OVERRIDE(void create(void *arg));

  MTHD_OVERRIDE(void destroy());

  /**
   * @brief Прикрепляет контекст к окну.
   *
   * @sa doneCurrent()
   */

  MTHD_OVERRIDE(auto makeCurrent() -> bool);

  /**
   * @brief Освобождаем контекст.
   *
   * @sa makeCurrent()
   */
  MTHD_OVERRIDE(auto doneCurrent() -> bool) {
    return true;
  }

  /**
   * @brief Обмен буферов.
   */
  MTHD_OVERRIDE(void present()) {}

  [[nodiscard]] auto getCanvasId() const -> std::string { return canvasId_; }

private:
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context_;
  std::string canvasId_;
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WEB_EMSCONTEXT_HPP
