#ifndef SWAY_PLTF_TYPEDEFS_HPP
#define SWAY_PLTF_TYPEDEFS_HPP

#include <sway/core.hpp>

#include <map>
#include <memory>  // std::shared_ptr

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

using DTPScreenConnectionRef_t = std::shared_ptr<class DTPScreenConnection>;
using DTPContextRef_t = std::shared_ptr<class DTPContext>;
using DTPCanvasRef_t = std::shared_ptr<class DTPCanvas>;

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_TYPEDEFS_HPP
