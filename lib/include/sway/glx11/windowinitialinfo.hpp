#ifndef SWAY_GLX11_WINDOWINITIALINFO_HPP
#define SWAY_GLX11_WINDOWINITIALINFO_HPP

#include <sway/glx11/windowsize.hpp>
#include <sway/namespacemacros.hpp>
#include <sway/types.hpp>

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

#endif
