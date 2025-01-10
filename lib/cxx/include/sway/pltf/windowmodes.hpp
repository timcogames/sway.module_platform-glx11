#ifndef SWAY_PLTF_WINDOWMODES_HPP
#define SWAY_PLTF_WINDOWMODES_HPP

#include <sway/core.hpp>

namespace sway::pltf {

/**
 * @brief Перечисление режимов окна.
 */
enum class WindowMode : i32_t { NONE = 0, WINDOWED, FULLSCREEN, Latest };

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WINDOWMODES_HPP
