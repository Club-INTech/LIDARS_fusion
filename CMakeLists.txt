cmake_minimum_required(VERSION 3.10)
project(LIDARS_fusion)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_NAME "LIDARS_fusion")

file(GLOB_RECURSE SOURCES "./*/*/include/*.h" "./*/*/include/*.hpp" "./*/*/src/*.c" "./*/*/src/*.cpp")

include_directories(COM_HL/include)
include_directories(TRAITEMENTS/obstacles/include)

add_executable(LIDARS_fusion
        ${SOURCES}
        COM_HL/include/DataSocket.hpp
        COM_HL/src/DataSocket.cpp
        LICENSE
        README.md main.cpp
        Lidar.cpp Lidar.hpp TRAITEMENTS/obstacles/src/Create_obstacle.cpp TRAITEMENTS/obstacles/include/Create_obstacle.hpp TRAITEMENTS/obstacles/include/Obstacle.hpp TRAITEMENTS/obstacles/include/Bounds.hpp)

add_subdirectory(ROBERT_RP)
add_subdirectory(TIM_SICK)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS window system graphics )
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


