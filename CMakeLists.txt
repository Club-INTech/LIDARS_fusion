cmake_minimum_required(VERSION 3.10)
project(LIDARS_fusion)

set(CMAKE_CXX_STANDARD 11)

include_directories(COM_HL/include)
include_directories(ROBERT_RP/basic_com/include)
include_directories(ROBERT_RP/lidar/include)
include_directories(ROBERT_RP/lidar_wrapper)
include_directories(ROBERT_RP/lidar_wrapper/include)
include_directories(TIM_SICK/basic_com/include)
include_directories(TIM_SICK/lidar/include)
include_directories(TRAITEMENTS/obstacles/include)

add_subdirectory(ROBERT_RP)
add_subdirectory(TIM_SICK)

add_executable(LIDARS_fusion
        COM_HL/include/DataSocket.hpp
        COM_HL/src/DataSocket.cpp
        LICENSE
        README.md main.cpp)
