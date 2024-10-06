#ifndef SWAY_PLTF_WINDOWMODES_HPP
#define SWAY_PLTF_WINDOWMODES_HPP

#include <sway/core.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

/**
 * @brief Перечисление режимов окна.
 */
enum class WindowMode : i32_t { NONE = 0, WINDOWED, FULLSCREEN, Latest };

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_WINDOWMODES_HPP
