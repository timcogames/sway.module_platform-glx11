#ifndef SWAY_GLX11_WINDOWMODES_HPP
#define SWAY_GLX11_WINDOWMODES_HPP

#include <sway/namespacemacros.hpp>
#include <sway/types.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/**
 * @brief Перечисление режимов окна.
 */
enum class WindowMode : s32_t {
  WINDOWED,  // Оконный режим.
  FULLSCREEN  // Полноэкранный режим.
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif  // SWAY_GLX11_WINDOWMODES_HPP
