#--------------------------------------------------------------------------------
# CMake version
#--------------------------------------------------------------------------------

cmake_minimum_required(VERSION 3.25.0 FATAL_ERROR)

set(META_PLTF_PRJNAME_TESTS "module_pltf_tests")
set(META_PLTF_EXENAME_TESTS "${META_PLTF_PRJNAME_TESTS}")

project(${META_PLTF_PRJNAME_TESTS} CXX)
enable_testing()

set(GTEST_ROOT "${GLOB_GTEST_ROOT_DIR}")
set(GTEST_INC_DIR "${GTEST_ROOT}/include")
set(GTEST_SRC_DIR "${GTEST_ROOT}/src")

set(GMOCK_ROOT "${GLOB_GMOCK_ROOT_DIR}")
set(GMOCK_INC_DIR "${GMOCK_ROOT}/include")

include_directories(${GTEST_INC_DIR} ${GMOCK_INC_DIR})

file(GLOB MODULE_PLTF_SOURCE_TESTS "${PROJECT_SOURCE_DIR}/*.spec.cpp")

# find_package(X11 REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L/opt/X11/lib")

add_executable(${META_PLTF_EXENAME_TESTS} ${MODULE_PLTF_SOURCE_TESTS} "${GTEST_SRC_DIR}/gtest_main.cc")
target_link_libraries(${META_PLTF_EXENAME_TESTS} module_core_obj X11 pthread ${GLOB_GTEST_LIB_DIR}/libgtest.a ${GLOB_GMOCK_LIB_DIR}/libgmock.a)
enable_cxx17(${META_PLTF_EXENAME_TESTS})

add_test(NAME ${META_PLTF_EXENAME_TESTS} COMMAND ${META_PLTF_EXENAME_TESTS})
