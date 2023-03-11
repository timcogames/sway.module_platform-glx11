# Проверяем версию CMake
cmake_minimum_required(VERSION 3.14.3 FATAL_ERROR)

include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_enable_cxx17.cmake")
include("${CMAKE_CURRENT_SOURCE_DIR}/submodules/sway.module_core/cmakehelpers/custom_add_subdirectory.cmake")

# Мета-информация о проекте
set(META_PLATFORM_GLX11_PRJNAME "module_platform_glx11")
set(META_PLATFORM_GLX11_LIBNAME "lib${META_PLATFORM_GLX11_PRJNAME}")
set(META_PLATFORM_GLX11_VERSION_MAJOR 0)
set(META_PLATFORM_GLX11_VERSION_MINOR 6)
set(META_PLATFORM_GLX11_VERSION_PATCH 12)
set(META_PLATFORM_GLX11_VERSION ${META_PLATFORM_GLX11_VERSION_MAJOR}.${META_PLATFORM_GLX11_VERSION_MINOR}.${META_PLATFORM_GLX11_VERSION_PATCH})

# Опции сборки
option(MODULE_PLATFORM_GLX11_SHARED_LIB "Build shared library (.so)" OFF)
option(MODULE_PLATFORM_GLX11_ENABLE_TESTS "Enable test builds" OFF)
option(CUSTOM_BOOST_ROOT_DIR "Boost root directory" OFF)
option(CUSTOM_GTEST_ROOT_DIR "GTest root directory" OFF)

project(${META_PLATFORM_GLX11_PRJNAME} VERSION ${META_PLATFORM_GLX11_VERSION} LANGUAGES CXX)

# Подмодули
if (NOT TARGET libmodule_core)
  custom_add_subdirectory("libmodule_core" submodules/sway.module_core)
endif()

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
set(MODULE_PLATFORM_GLX11_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories("${GLUT_INCLUDE_DIRS}")
include_directories("${MODULE_PLATFORM_GLX11_DIR}/lib/include")
include_directories("${MODULE_PLATFORM_GLX11_DIR}/submodules/sway.module_core/lib/include")
include_directories("${MODULE_PLATFORM_GLX11_DIR}/submodules/sway.module_math/lib/include")

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_PLATFORM_GLX11_HEADERS ${MODULE_PLATFORM_GLX11_DIR}/lib/include/*.*)
file(GLOB_RECURSE MODULE_PLATFORM_GLX11_SOURCE ${MODULE_PLATFORM_GLX11_DIR}/lib/src/*.*)

link_directories("${GLUT_LIBRARY_DIRS}")

find_package(OpenGL REQUIRED)
find_package(X11 QUIET)

if (MODULE_PLATFORM_GLX11_SHARED_LIB)
  # Добавляем в проект цель для сборки динамической библиотеки
  add_library(${META_PLATFORM_GLX11_LIBNAME} SHARED ${MODULE_PLATFORM_GLX11_SOURCE})
  set_target_properties(${META_PLATFORM_GLX11_LIBNAME} PROPERTIES OUTPUT_NAME ${META_PLATFORM_GLX11_PRJNAME})
  set_target_properties(${META_PLATFORM_GLX11_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_PLATFORM_GLX11_LIBNAME} PROPERTIES SUFFIX ".so.${META_PLATFORM_GLX11_VERSION}")
else ()
  # Добавляем в проект цель для сборки статической библиотеки
  add_library(${META_PLATFORM_GLX11_LIBNAME} STATIC ${MODULE_PLATFORM_GLX11_SOURCE})
  set_target_properties(${META_PLATFORM_GLX11_LIBNAME} PROPERTIES OUTPUT_NAME ${META_PLATFORM_GLX11_PRJNAME})
  set_target_properties(${META_PLATFORM_GLX11_LIBNAME} PROPERTIES PREFIX "")
  set_target_properties(${META_PLATFORM_GLX11_LIBNAME} PROPERTIES SUFFIX ".a.${META_PLATFORM_GLX11_VERSION}")
endif ()

custom_enable_cxx17(${META_PLATFORM_GLX11_LIBNAME})
target_link_libraries(${META_PLATFORM_GLX11_LIBNAME} GL X11)

add_subdirectory(examples/window)
