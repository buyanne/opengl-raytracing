cmake_minimum_required(VERSION 3.20)
project(gl)
include_directories(include)
link_directories(lib/x64)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(gl main.cpp entity/Vector3d.cpp entity/Vector3d.h entity/Color.h entity/Light.h entity/Ray.h entity/Object.h entity/sphere.cpp entity/sphere.h entity/plane.cpp entity/plane.h)

target_link_libraries(gl libopengl32.a  libfreeglut.a)

