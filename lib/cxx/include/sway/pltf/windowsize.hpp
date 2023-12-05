#ifndef SWAY_PLTF_WINDOWSIZE_HPP
#define SWAY_PLTF_WINDOWSIZE_HPP

#include <sway/core.hpp>
#include <sway/math/size.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

struct WindowSize {
  math::size2i_t normal;  // Нормальный размер окна.
  math::size2i_t min;  // Минимальный размер окна.
  math::size2i_t max;  // Максимальный размер окна.
};

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_WINDOWSIZE_HPP
