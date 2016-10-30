cmake_minimum_required (VERSION 3.5) # in reality I'm sure it's less
project(gravity)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

add_executable(gravity geometry.cpp gravity.cpp physics.cpp sofp_opengl.cpp sofp_sdl.cpp)

find_package(OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(gravity ${OPENGL_LIBRARIES})

find_package(SDL2)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(gravity ${SDL2_LIBRARY})
