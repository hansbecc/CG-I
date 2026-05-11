
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <algorithm>
#include <iostream>

struct Punto { int x, y; };

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec2 aPos;
void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec3 color;
void main() {
    FragColor = vec4(color, 1.0);
}
)";

GLuint crearShader() {
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShaderSource, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShaderSource, NULL);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

// Convierte coordenadas de pantalla a OpenGL (-1,1)
float normX(int x, int width) { return (float)x / width * 2.0f - 1.0f; }
float normY(int y, int height) { return (float)y / height * 2.0f - 1.0f; }

std::vector<float> scanlineFill(std::vector<Punto>& poly, int width, int height) {
    //COMPLETAR CÓDIGO
}

int main() {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800, 600, "Scanline OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);

    glewInit();

    GLuint shader = crearShader();

    std::vector<Punto> poligono = {
        {200, 150}, {600, 150}, {700, 400}, {400, 500}, {150, 400}
    };

    std::vector<float> pixels = scanlineFill(poligono, 800, 600);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, pixels.size()*sizeof(float), pixels.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniform3f(glGetUniformLocation(shader, "color"), 0.2f, 0.7f, 0.3f);

        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, pixels.size()/2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
