#ifndef SWAY_PLTF_WEB_EMSCONTEXT_HPP
#define SWAY_PLTF_WEB_EMSCONTEXT_HPP

#include <sway/core.hpp>
#include <sway/pltf/context.hpp>

#include <emscripten.h>
#include <emscripten/html5.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class EMSContext : public Context {
public:
  EMSContext();

  virtual ~EMSContext();

  MTHD_OVERRIDE(void create(void *config));

  void destroy();

  /**
   * @brief Прикрепляет контекст к окну.
   *
   * @sa doneCurrent()
   */
  // clang-format off
  MTHD_OVERRIDE(auto makeCurrent() -> bool);  // clang-format on

  /**
   * @brief Освобождаем контекст.
   *
   * @sa makeCurrent()
   */
  // clang-format off
  MTHD_OVERRIDE(auto doneCurrent() -> bool) {  // clang-format on
    return true;
  }

  /**
   * @brief Обмен буферов.
   */
  MTHD_OVERRIDE(void present()) {}

  auto getTargetId() const -> std::string { return targetId_; }

private:
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context_;
  std::string targetId_;
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WEB_EMSCONTEXT_HPP
