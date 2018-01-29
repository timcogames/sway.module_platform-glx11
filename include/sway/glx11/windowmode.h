#ifndef SWAY_GLX11_WINDOWMODE_H
#define SWAY_GLX11_WINDOWMODE_H

#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief
 *    Перечисление режимов окна.
 */
enum WindowMode {
	kWindowMode_Windowed = 0, /*!< Оконный режим. */
	kWindowMode_Fullscreen = 1 /*!< Полноэкранный режим. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_WINDOWMODE_H
