cmake_minimum_required(VERSION 3.21)
#set (CMAKE_OSX_ARCHITECTURES arm64 x86_64)


project(physics)
set(CMAKE_CXX_STANDARD 20)

add_library(glut_manager matrix.cpp matrix.hpp)

find_library(GLUT glut)
find_package(OpenGL REQUIRED)
message("Glut is ${GLUT}")
target_compile_definitions(glut_manager PUBLIC GL_SILENCE_DEPRECATION)
target_link_libraries(glut_manager PUBLIC ${GLUT} ${OPENGL_LIBRARIES})


add_executable(physics main.cpp particle.cpp particle.hpp bond.cpp bond.hpp simulation.cpp simulation.hpp)

target_link_libraries(physics glut_manager)

