#ifndef SWAY_GLX11_WINDOWSIZE_H
#define SWAY_GLX11_WINDOWSIZE_H

#include <sway/math/size.h>
#include <sway/namespacemacros.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowSize {
	math::size2i_t normal; /*!< Нормальный размер окна. */
	math::size2i_t min; /*!< Минимальный размер окна. */
	math::size2i_t max; /*!< Максимальный размер окна. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_WINDOWSIZE_H
