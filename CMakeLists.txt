cmake_minimum_required(VERSION 3.10)
project(LIDARS_fusion)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_NAME "LIDARS_fusion")

file(GLOB_RECURSE SOURCES "./*/include/*.h" "./*/include/*.hpp" "./*/src/*.c" "./*/src/*.cpp")

include_directories(COM_HL/include)
include_directories(TRAITEMENTS/include)

add_executable(LIDARS_fusion
        ${SOURCES}
        main.cpp)

add_subdirectory(LIDARS/RPLIDAR_A2)
add_subdirectory(LIDARS/TIM561)
include_directories(LIDARS/RPLIDAR_A2/include)
include_directories(LIDARS/TIM561/include)
target_link_libraries(${EXECUTABLE_NAME} LIB_TIM)
target_link_libraries(${EXECUTABLE_NAME} LIB_RPLIDAR)
# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML REQUIRED COMPONENTS window system graphics audio )
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


