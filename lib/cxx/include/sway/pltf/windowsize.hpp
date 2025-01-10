#ifndef SWAY_PLTF_WINDOWSIZE_HPP
#define SWAY_PLTF_WINDOWSIZE_HPP

#include <sway/core.hpp>
#include <sway/math/size.hpp>

namespace sway::pltf {

struct WindowSize {
  math::size2i_t normal;  // Нормальный размер окна.
  math::size2i_t min;  // Минимальный размер окна.
  math::size2i_t max;  // Максимальный размер окна.
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WINDOWSIZE_HPP
