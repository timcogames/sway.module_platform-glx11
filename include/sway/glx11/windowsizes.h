#ifndef SWAY_GLX11_WINDOWSIZES_H
#define SWAY_GLX11_WINDOWSIZES_H

#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief
 *    Перечисление размеров окна.
 */
enum class WindowSize_t : s32_t {
	kOrigin, /*!< Основной размер. */
	kMin, /*!< Минимальный размер окна. */
	kMax, /*!< Максимальный размер окна. */
	kLast
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_WINDOWSIZES_H
