# Проверяем версию CMake
cmake_minimum_required(VERSION 3.10.2 FATAL_ERROR)

# Мета-информация о проекте
set(META_PROJECT_NAME module_platform_glx11)
set(META_LIB_NAME lib${META_PROJECT_NAME})
set(META_VERSION_MAJOR 0)
set(META_VERSION_MINOR 2)
set(META_VERSION_PATCH 3)
set(META_VERSION ${META_VERSION_MAJOR}.${META_VERSION_MINOR}.${META_VERSION_PATCH})

# Опции сборки
option(BUILD_SHARED "Build shared library" OFF)

project(${META_PROJECT_NAME} C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Определяем каталог вывода по умолчанию
if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/dbg)
else()
	set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
	set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif()

set(MODULE_PLATFORM_GLX11_DIR ${CMAKE_CURRENT_LIST_DIR})

# Добавляем пути для поиска хедеров
include_directories(${MODULE_PLATFORM_GLX11_DIR}/include)
include_directories(${MODULE_PLATFORM_GLX11_DIR}/modules/sway.module_core/include)
include_directories(${MODULE_PLATFORM_GLX11_DIR}/modules/sway.module_math/include)

# Получаем пути ко всем хедерам и исходникам библиотеки
file(GLOB_RECURSE MODULE_PLATFORM_GLX11_HEADERS ${MODULE_PLATFORM_GLX11_DIR}/include/*.*)
file(GLOB_RECURSE MODULE_PLATFORM_GLX11_SOURCE ${MODULE_PLATFORM_GLX11_DIR}/src/*.*)

find_package(OpenGL REQUIRED)
find_package(X11 REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
set(BOOST_COMPONENTS system filesystem thread)
find_package(Boost 1.58 REQUIRED COMPONENTS ${BOOST_COMPONENTS})
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Fatal error: Boost (version >= 1.58) required.")
else()
	message(STATUS "Boost includes: ${Boost_INCLUDE_DIRS}")
	message(STATUS "Boost libs: ${Boost_LIBRARIES}")

	include_directories(${Boost_INCLUDE_DIRS})
endif()

if(BUILD_SHARED)
	# Добавляем в проект цель для сборки статической библиотеки
	add_library(${META_LIB_NAME} SHARED ${MODULE_PLATFORM_GLX11_SOURCE})
	set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
	set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
	set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".so.${META_VERSION}")
else()
	# Добавляем в проект цель для сборки динамической библиотеки
	add_library(${META_LIB_NAME} STATIC ${MODULE_PLATFORM_GLX11_SOURCE})
	set_target_properties(${META_LIB_NAME} PROPERTIES OUTPUT_NAME ${META_PROJECT_NAME})
	set_target_properties(${META_LIB_NAME} PROPERTIES PREFIX "")
	set_target_properties(${META_LIB_NAME} PROPERTIES SUFFIX ".a.${META_VERSION}")
endif()

target_link_libraries(${META_PROJECT_NAME} X11 Boost::system Boost::filesystem Boost::thread)
