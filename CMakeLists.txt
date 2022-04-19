cmake_minimum_required(VERSION 3.20)
project(gl)
include_directories(include)
link_directories(lib/x64)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(gl main.cpp Vector3d.cpp Vector3d.h Color.h Light.h Ray.h Object.h sphere.cpp sphere.h plane.cpp plane.h)

target_link_libraries(gl libopengl32.a  libfreeglut.a)

