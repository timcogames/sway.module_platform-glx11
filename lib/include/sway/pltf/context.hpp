#ifndef SWAY_PLTF_CONTEXT_HPP
#define SWAY_PLTF_CONTEXT_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

class Context {
public:
  virtual ~Context() = default;

  PURE_VIRTUAL(void create(void *config));

  // clang-format off
  PURE_VIRTUAL(auto makeCurrent() -> bool);  // clang-format on

  // clang-format off
  PURE_VIRTUAL(auto doneCurrent() -> bool);  // clang-format on

  PURE_VIRTUAL(void present());
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_CONTEXT_HPP
