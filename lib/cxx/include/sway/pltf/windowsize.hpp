#ifndef SWAY_PLTF_WINDOWSIZE_HPP
#define SWAY_PLTF_WINDOWSIZE_HPP

#include <sway/core.hpp>
#include <sway/math/size.hpp>

namespace sway::pltf {

struct WindowSize {
  math::size2i_t normal;  //!< \~russian Нормальный размер окна.
  math::size2i_t min;  //!< \~russian Минимальный размер окна.
  math::size2i_t max;  //!< \~russian Максимальный размер окна.
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WINDOWSIZE_HPP
