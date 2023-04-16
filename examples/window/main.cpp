#include <sway/core.hpp>
#include <sway/math.hpp>
#include <sway/pltf/mac/dtpcanvas.hpp>
#include <sway/pltf/mac/dtpscreenconnection.hpp>

#include <memory>  // std::shared_ptr, std::make_shared

using namespace sway;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
  pltf::WindowInitialInfo windowInitialInfo;
  windowInitialInfo.title = "window";
  windowInitialInfo.size.normal = math::size2i_t(800, 600);
  windowInitialInfo.fullscreen = false;
  windowInitialInfo.resizable = false;

  auto connection = std::make_shared<pltf::DTPScreenConnection>();
  auto canvas = std::make_shared<pltf::DTPCanvas>(connection, windowInitialInfo);

  canvas->show();
  canvas->getContext()->makeCurrent();

  while (canvas->eventLoop(true)) {
    canvas->getContext()->makeCurrent();

    canvas->getContext()->present();
    canvas->getContext()->doneCurrent();
  }

  return 0;
}
