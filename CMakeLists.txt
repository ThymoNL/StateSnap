cmake_minimum_required(VERSION 3.20)
project(StateSnap)

set(CMAKE_CXX_STANDARD 17)

set(ORBITER_LIB_DIR ${ORBITER_SDK_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${ORBITER_PLUGIN_DIR})

add_library(StateSnap SHARED StateSnap.cpp Resources.rc resource.h)

target_include_directories(StateSnap
        PUBLIC ${ORBITER_SDK_DIR}/include)

target_link_libraries(StateSnap
        ${ORBITER_LIB_DIR}/orbiter.lib
        ${ORBITER_LIB_DIR}/Orbitersdk.lib)
