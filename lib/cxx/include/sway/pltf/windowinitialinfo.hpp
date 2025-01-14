#ifndef SWAY_PLTF_WINDOWINITIALINFO_HPP
#define SWAY_PLTF_WINDOWINITIALINFO_HPP

#include <sway/core.hpp>
#include <sway/pltf/windowsize.hpp>

namespace sway::pltf {

struct WindowInitialInfo {
  lpcstr_t title;  //!< \~russian Заголовок окна.
  WindowSize size;  //!< \~russian Размер окна.
  bool resizable;  //!< \~russian Возможность изменения размера.
  bool fullscreen;  //!< \~russian Полноэкранный / Оконный режим.
  bool maximized;
  bool vsync;
};

}  // namespace sway::pltf

#endif  // SWAY_PLTF_WINDOWINITIALINFO_HPP
