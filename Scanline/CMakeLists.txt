
cmake_minimum_required(VERSION 3.10)
project(OpenGLScanline)

set(CMAKE_CXX_STANDARD 17)
set(OpenGL_GL_PREFERENCE GLVND) 
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(scanline main.cpp)

target_link_libraries(scanline OpenGL::GL GLEW::GLEW glfw)
