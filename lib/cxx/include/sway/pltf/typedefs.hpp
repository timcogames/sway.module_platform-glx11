#ifndef SWAY_PLTF_TYPEDEFS_HPP
#define SWAY_PLTF_TYPEDEFS_HPP

#include <sway/core.hpp>

namespace sway::pltf {

class Context;

class Loopeable;

class DTPScreenConnection;

namespace typedefs {

using ContextSharedPtr_t = std::shared_ptr<Context>;

using LoopeableSharedPtr_t = std::shared_ptr<Loopeable>;

using DTPScreenConnectionSharedPtr_t = std::shared_ptr<DTPScreenConnection>;

}  // namespace typedefs

}  // namespace sway::pltf

#endif  // SWAY_PLTF_TYPEDEFS_HPP
