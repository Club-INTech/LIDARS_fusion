cmake_minimum_required(VERSION 3.10)
project(LIDARS_fusion)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES "./*/*/include/*.h" "./*/*/include/*.hpp" "./*/*/src/*.c" "./*/*/src/*.cpp")

include_directories(COM_HL/include)
include_directories(TRAITEMENTS/obstacles/include)

add_executable(LIDARS_fusion
        ${SOURCES}
        COM_HL/include/DataSocket.hpp
        COM_HL/src/DataSocket.cpp
        LICENSE
        README.md main.cpp
        Lidar.cpp Lidar.hpp)

add_subdirectory(ROBERT_RP)
add_subdirectory(TIM_SICK)


