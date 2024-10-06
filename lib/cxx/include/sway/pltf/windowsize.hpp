#ifndef SWAY_PLTF_WINDOWSIZE_HPP
#define SWAY_PLTF_WINDOWSIZE_HPP

#include <sway/core.hpp>
#include <sway/math/size.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

struct WindowSize {
  math::size2i_t normal;  // Нормальный размер окна.
  math::size2i_t min;  // Минимальный размер окна.
  math::size2i_t max;  // Максимальный размер окна.
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_WINDOWSIZE_HPP
