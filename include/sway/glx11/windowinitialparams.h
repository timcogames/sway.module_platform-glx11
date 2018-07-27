#ifndef SWAY_GLX11_WINDOWINITIALPARAMS_H
#define SWAY_GLX11_WINDOWINITIALPARAMS_H

#include <sway/glx11/windowsizes.h>
#include <sway/math.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowInitialParams {
	lpcstr_t title; /*!< Заголовок окна. */
	math::size2i_t sizes[core::detail::toUnderlying(WindowSize_t::kLast)]; /*!< Размеры окна. */
	bool resizable; /*!< Возможность изменения размера. */
	bool fullscreen; /*!< Полноэкранный / Оконный режим. */
	bool maximized;
	bool vsync;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_WINDOWINITIALPARAMS_H
