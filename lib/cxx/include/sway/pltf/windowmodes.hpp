#ifndef SWAY_PLTF_WINDOWMODES_HPP
#define SWAY_PLTF_WINDOWMODES_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

/**
 * @brief Перечисление режимов окна.
 */
enum class WindowMode : i32_t { NONE = 0, WINDOWED, FULLSCREEN, Latest };

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WINDOWMODES_HPP
