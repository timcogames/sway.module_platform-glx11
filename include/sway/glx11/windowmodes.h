#ifndef SWAY_GLX11_WINDOWMODES_H
#define SWAY_GLX11_WINDOWMODES_H

#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief
 *    Перечисление режимов окна.
 */
enum class WindowMode_t : s32_t {
	kWindowed, /*!< Оконный режим. */
	kFullscreen /*!< Полноэкранный режим. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_WINDOWMODES_H
