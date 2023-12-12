#---------------------------------------------------------------------------------
# CMake version
#---------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

#---------------------------------------------------------------------------------
# Project directories
#---------------------------------------------------------------------------------

set(MODULE_PLTF_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODULE_PLTF_LIST_DIR "${CMAKE_CURRENT_LIST_DIR}")
set(MODULE_PLTF_CMAKE_DIR "${MODULE_PLTF_ROOT_DIR}/submodules/sway.module_core/cmake_modules")
set(MODULE_PLTF_LIB_DIR "${MODULE_PLTF_ROOT_DIR}/lib")
set(MODULE_PLTF_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")

set(X11_INC_DIRS "/opt/X11/include")
set(X11_LIB_DIRS "/opt/X11/lib")

#---------------------------------------------------------------------------------
# Include CMake modules
#---------------------------------------------------------------------------------

include("${MODULE_PLTF_CMAKE_DIR}/options.cmake")
include("${MODULE_PLTF_CMAKE_DIR}/set_output_dir.cmake")
include("${MODULE_PLTF_CMAKE_DIR}/project_metadata.cmake")
include("${MODULE_PLTF_CMAKE_DIR}/enable_cxx17.cmake")
include("${MODULE_PLTF_CMAKE_DIR}/add_submodule.cmake")

#---------------------------------------------------------------------------------
# Build options
#---------------------------------------------------------------------------------

option(MODULE_PLTF_SHARED_LIB "Build shared library (dylib/.so)" OFF)
option(MODULE_PLTF_ENABLE_TESTS "Enable test builds" OFF)
option(MODULE_PLTF_ENABLE_EXAMPLES "Enable test builds" OFF)

#---------------------------------------------------------------------------------
# [EMSCRIPTEN]: Setup
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  emscripten_setup()
endif()

#---------------------------------------------------------------------------------
# Project
#---------------------------------------------------------------------------------

project_metadata("pltf" 0.7.0)
project(${MODULE_PLTF_PROJ_NAME} VERSION ${MODULE_PLTF_VERSION} LANGUAGES CXX)

#---------------------------------------------------------------------------------
# Submodules
#---------------------------------------------------------------------------------

add_submodule("module_core" submodules/sway.module_core)

if(GLOB_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_COMPILER "${EMSCRIPTEN_COMPILER}")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--whole-archive")
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-unicode-whitespace \
  #   -Wno-unused-local-typedef -Wno-invalid-noreturn -Wno-unused-command-line-argument")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")

#---------------------------------------------------------------------------------
# Executable output path
#---------------------------------------------------------------------------------

set_output_dir(${MODULE_PLTF_BIN_DIR})

#---------------------------------------------------------------------------------
# Include project headers
#---------------------------------------------------------------------------------

if(GLOB_EMSCRIPTEN_PLATFORM)
  include_directories("${GLOB_EMSCRIPTEN_ROOT_DIR}/cache/sysroot/include")
endif()
include_directories("${X11_INC_DIRS}")
include_directories("${MODULE_PLTF_LIST_DIR}/lib/cxx/include")
include_directories("${MODULE_PLTF_LIST_DIR}/submodules/sway.module_core/lib/cxx/include")
include_directories("${MODULE_PLTF_LIST_DIR}/submodules/sway.module_math/lib/cxx/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_PLTF_HEADERS ${MODULE_PLTF_LIST_DIR}/lib/cxx/include/*.*)
if(GLOB_EMSCRIPTEN_PLATFORM)
  file(GLOB_RECURSE MODULE_PLTF_SOURCE ${MODULE_PLTF_LIST_DIR}/lib/cxx/src/web/*.*)
else()
  file(GLOB_RECURSE MODULE_PLTF_SOURCE ${MODULE_PLTF_LIST_DIR}/lib/cxx/src/mac/*.*)
endif()

link_directories("${X11_LIB_DIRS}")

find_package(OpenGL REQUIRED)
find_package(X11 QUIET)

if(MODULE_PLTF_SHARED_LIB)
  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${MODULE_PLTF_TARGET} SHARED ${MODULE_PLTF_SOURCE})
  set_target_properties(${MODULE_PLTF_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_PLTF_LIB_NAME})
  set_target_properties(${MODULE_PLTF_TARGET} PROPERTIES PREFIX "")
  set_target_properties(${MODULE_PLTF_TARGET} PROPERTIES SUFFIX ".so")
else()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${MODULE_PLTF_TARGET} STATIC ${MODULE_PLTF_SOURCE})
  set_target_properties(${MODULE_PLTF_TARGET} PROPERTIES OUTPUT_NAME ${MODULE_PLTF_LIB_NAME})
  set_target_properties(${MODULE_PLTF_TARGET} PROPERTIES PREFIX "")
  set_target_properties(${MODULE_PLTF_TARGET} PROPERTIES SUFFIX ".a")
endif()

enable_cxx17(${MODULE_PLTF_TARGET})
target_link_libraries(${MODULE_PLTF_TARGET} GL X11)

#---------------------------------------------------------------------------------
# Examples
#---------------------------------------------------------------------------------

if(MODULE_PLTF_ENABLE_EXAMPLES)
  add_subdirectory(examples/window)
endif()
