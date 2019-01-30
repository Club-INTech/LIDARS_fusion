cmake_minimum_required(VERSION 3.10)
project(LIDARS_fusion)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_NAME "LIDARS_fusion")

file(GLOB_RECURSE SOURCES "./*/*/include/*.h" "./*/*/include/*.hpp" "./*/*/src/*.c" "./*/*/src/*.cpp")

include_directories(COM_HL/socket/include)
include_directories(TRAITEMENTS/obstacles/include)

add_executable(LIDARS_fusion
        ${SOURCES}
        main.cpp
        Lidar.cpp Lidar.hpp COM_HL/socket/include/DataSocket.hpp COM_HL/socket/src/DataSocket.cpp
        TRAITEMENTS/obstacles/src/Create_obstacle.cpp TRAITEMENTS/obstacles/include/Create_obstacle.hpp
        TRAITEMENTS/obstacles/include/Obstacle.hpp TRAITEMENTS/obstacles/include/Bounds.hpp
        TRAITEMENTS/graphics/include/Show.hpp TRAITEMENTS/graphics/src/Show.cpp
        TRAITEMENTS/sounds/include/Play.hpp TRAITEMENTS/sounds/src/Play.cpp)

add_subdirectory(ROBERT_RP)
add_subdirectory(TIM_SICK)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS window system graphics audio )
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


