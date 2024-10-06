#ifndef SWAY_PLTF_WINDOWINITIALINFO_HPP
#define SWAY_PLTF_WINDOWINITIALINFO_HPP

#include <sway/core.hpp>
#include <sway/pltf/windowsize.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(pltf)

struct WindowInitialInfo {
  lpcstr_t title;  // Заголовок окна.
  WindowSize size;  // Размер окна.
  bool resizable;  // Возможность изменения размера.
  bool fullscreen;  // Полноэкранный / Оконный режим.
  bool maximized;
  bool vsync;
};

NS_END()  // namespace pltf
NS_END()  // namespace sway

#endif  // SWAY_PLTF_WINDOWINITIALINFO_HPP
