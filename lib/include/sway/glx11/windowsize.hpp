#ifndef SWAY_GLX11_WINDOWSIZE_HPP
#define SWAY_GLX11_WINDOWSIZE_HPP

#include <sway/math/size.hpp>
#include <sway/namespacemacros.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(glx11)

struct WindowSize {
  math::size2i_t normal; /*!< Нормальный размер окна. */
  math::size2i_t min; /*!< Минимальный размер окна. */
  math::size2i_t max; /*!< Максимальный размер окна. */
};

NAMESPACE_END(glx11)
NAMESPACE_END(sway)

#endif
