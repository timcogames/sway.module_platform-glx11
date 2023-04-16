#ifndef SWAY_PLTF_TYPEDEFS_HPP
#define SWAY_PLTF_TYPEDEFS_HPP

#include <sway/namespacemacros.hpp>
#include <sway/types.hpp>

#include <map>
#include <memory>  // std::shared_ptr

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(pltf)

typedef std::shared_ptr<class DTPScreenConnection> DTPScreenConnectionRef_t;
typedef std::shared_ptr<class DTPContext> DTPContextRef_t;
typedef std::shared_ptr<class DTPCanvas> DTPCanvasRef_t;

NAMESPACE_END(pltf)
NAMESPACE_END(sway)

#endif  // SWAY_PLTF_TYPEDEFS_HPP
