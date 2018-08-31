#ifndef SWAY_GLX11_WINDOWINITIALINFO_H
#define SWAY_GLX11_WINDOWINITIALINFO_H

#include <sway/glx11/windowsize.h>
#include <sway/namespacemacros.h>
#include <sway/types.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowInitialInfo {
	lpcstr_t title; /*!< Заголовок окна. */
	WindowSize size; /*!< Размер окна. */
	bool resizable; /*!< Возможность изменения размера. */
	bool fullscreen; /*!< Полноэкранный / Оконный режим. */
	bool maximized;
	bool vsync;
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif // SWAY_GLX11_WINDOWINITIALINFO_H
