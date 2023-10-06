cmake_minimum_required(VERSION 3.12)

project(sdl_cpp_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")

project(sdl_cpp_game)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
                    ${SDL2_IMAGE_INCLUDE_DIR}
                    ${SDL2_TTF_INCLUDE_DIR})

include_directories("fonts")
include_directories("images")
include_directories("includes")

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE INCLUDES "includes/*.h")

add_executable(sdl_cpp_game ${SOURCES} ${INCLUDES})

target_link_libraries(sdl_cpp_game ${SDL2_LIBRARY}
                             ${SDL2_IMAGE_LIBRARIES}
                             ${SDL2_TTF_LIBRARIES})
