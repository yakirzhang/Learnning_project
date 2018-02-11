cmake_minimum_required(VERSION 3.8)
project(testc)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(THIRDPARTY_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty)
# 3rd include and libs
include(3rdparty)

add_subdirectory(Templates)
add_subdirectory(DesignModel)
add_subdirectory(ZMQ)
add_subdirectory(FeatureCPP)
add_subdirectory(Opencv)
add_subdirectory(Gflags)
add_subdirectory(Eigentests)

