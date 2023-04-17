# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_add_subdirectory.cmake")

# Мета-информация о проекте
set(META_PLTF_PRJNAME "module_pltf")
set(META_PLTF_LIBNAME "lib${META_PLTF_PRJNAME}")
set(META_PLTF_VERSION_MAJOR 0)
set(META_PLTF_VERSION_MINOR 6)
set(META_PLTF_VERSION_PATCH 12)
set(META_PLTF_VERSION ${META_PLTF_VERSION_MAJOR}.${META_PLTF_VERSION_MINOR}.${META_PLTF_VERSION_PATCH})

# Опции сборки
option(MODULE_PLTF_SHARED_LIB "Build shared library (.so)" OFF)
option(MODULE_PLTF_ENABLE_TESTS "Enable test builds" OFF)
option(GLOBAL_EMSCRIPTEN_PLATFORM "Using emscripten compiler" OFF)
option(GLOBAL_EMSCRIPTEN_USE_BINDING "Using emscripten binding" OFF)
option(CUSTOM_EMSCRIPTEN_ROOT_DIR "Emscripten root directory" OFF)
option(CUSTOM_BOOST_ROOT_DIR "Boost root directory" OFF)
option(CUSTOM_GTEST_ROOT_DIR "GTest root directory" OFF)

project(${META_PLTF_PRJNAME} VERSION ${META_PLTF_VERSION} LANGUAGES CXX)

set(CMAKE_OSX_SYSROOT "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk")

if (GLOBAL_EMSCRIPTEN_PLATFORM AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "${CUSTOM_EMSCRIPTEN_ROOT_DIR}/cmake/Modules/Platform/Emscripten.cmake")
  include(${CMAKE_TOOLCHAIN_FILE})
endif ()

# Подмодули
if (NOT TARGET libmodule_core)
  custom_add_subdirectory("libmodule_core" submodules/sway.module_core)
endif()

if (GLOBAL_EMSCRIPTEN_PLATFORM)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM")
  if (GLOBAL_EMSCRIPTEN_USE_BINDING)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --bind")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEMSCRIPTEN_PLATFORM_USE_BINDING")
  endif ()
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIE")

# Определяем каталог вывода по умолчанию
if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else ()
  set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif ()

set(GLUT_INCLUDE_DIRS "/opt/X11/include")
set(GLUT_LIBRARY_DIRS "/opt/X11/lib")
set(MODULE_PLTF_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
if (GLOBAL_EMSCRIPTEN_PLATFORM)
  include_directories("${CUSTOM_EMSCRIPTEN_ROOT_DIR}/cache/sysroot/include")
endif ()
include_directories("${GLUT_INCLUDE_DIRS}")
include_directories("${MODULE_PLTF_DIR}/lib/include")
include_directories("${MODULE_PLTF_DIR}/submodules/sway.module_core/lib/include")
include_directories("${MODULE_PLTF_DIR}/submodules/sway.module_math/lib/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_PLTF_HEADERS ${MODULE_PLTF_DIR}/lib/include/*.*)
if (GLOBAL_EMSCRIPTEN_PLATFORM)
  file(GLOB_RECURSE MODULE_PLTF_SOURCE ${MODULE_PLTF_DIR}/lib/src/web/*.*)
else ()
  file(GLOB_RECURSE MODULE_PLTF_SOURCE ${MODULE_PLTF_DIR}/lib/src/mac/*.*)
endif ()

link_directories("${GLUT_LIBRARY_DIRS}")

find_package(OpenGL REQUIRED)
find_package(X11 QUIET)

if (MODULE_PLTF_SHARED_LIB)
  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_PLTF_LIBNAME} SHARED ${MODULE_PLTF_SOURCE})
  set_target_properties(${META_PLTF_LIBNAME} PROPERTIES OUTPUT_NAME ${META_PLTF_PRJNAME})
  set_target_properties(${META_PLTF_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_PLTF_LIBNAME} PROPERTIES SUFFIX ".so.${META_PLTF_VERSION}")
else ()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_PLTF_LIBNAME} STATIC ${MODULE_PLTF_SOURCE})
  set_target_properties(${META_PLTF_LIBNAME} PROPERTIES OUTPUT_NAME ${META_PLTF_PRJNAME})
  set_target_properties(${META_PLTF_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_PLTF_LIBNAME} PROPERTIES SUFFIX ".a.${META_PLTF_VERSION}")
endif ()

custom_enable_cxx17(${META_PLTF_LIBNAME})
target_link_libraries(${META_PLTF_LIBNAME} GL X11)

if (MODULE_PLTF_ENABLE_TESTS)
  add_subdirectory(examples/window)
endif ()
