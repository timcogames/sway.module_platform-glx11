# Мета-информация о проекте
set(META_PRJNAME_EXAMPLES "module_pltf_examples_window")
set(META_EXENAME_EXAMPLES "lib${META_PRJNAME_EXAMPLES}")

project(${META_PRJNAME_EXAMPLES} CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Получаем пути ко всем исходникам с тестами
file(GLOB MODULE_GAPI_SOURCE_EXAMPLES "${PROJECT_SOURCE_DIR}/*.cpp")

add_executable(${META_EXENAME_EXAMPLES} ${MODULE_GAPI_SOURCE_EXAMPLES})

target_link_libraries(${META_EXENAME_EXAMPLES} GLU module_pltf module_core)
