#ifndef SWAY_GLX11_WINDOWSIZE_H
#define SWAY_GLX11_WINDOWSIZE_H

#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

/*!
 * \brief
 *    Перечисление размеров окна.
 */
enum WindowSize {
	kWindowSize = 0, /*!< Основной размер. */
	kWindowSize_Min = 1, /*!< Минимальный размер окна. */
	kWindowSize_Max = 2, /*!< Максимальный размер окна. */
	kWindowSize_Last
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_WINDOWSIZE_H
