cmake_minimum_required(VERSION 3.20)
project(gl)
include_directories(src/include)
link_directories(src/lib/x64)

set(CMAKE_C_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(gl main.cpp src/entity/Vector3d.cpp src/entity/Vector3d.h src/entity/Color.h src/entity/Light.h src/entity/Ray.h src/entity/Object.h src/entity/sphere.cpp src/entity/sphere.h src/entity/plane.cpp src/entity/plane.h)

target_link_libraries(gl libopengl32.a  libfreeglut.a)

