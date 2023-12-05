#ifndef SWAY_PLTF_WINDOWMODES_HPP
#define SWAY_PLTF_WINDOWMODES_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

/**
 * @brief Перечисление режимов окна.
 */
enum class WindowMode : s32_t {
  WINDOWED,  // Оконный режим.
  FULLSCREEN  // Полноэкранный режим.
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WINDOWMODES_HPP
