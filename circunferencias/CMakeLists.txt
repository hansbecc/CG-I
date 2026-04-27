cmake_minimum_required(VERSION 3.10)
project(CircunferenciasOpenGL)

set(CMAKE_CXX_STANDARD 17)

# Buscar paquetes necesarios
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

# Agregar el ejecutable
add_executable(Circunferencias main.cpp)

# Enlazar librerías
target_link_libraries(Circunferencias 
    PRIVATE 
    OpenGL::GL 
    GLEW::GLEW 
    glfw 
    glm::glm
)