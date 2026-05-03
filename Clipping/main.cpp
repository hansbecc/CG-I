#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Constantes de región (Outcodes) [cite: 16, 51-54]
const int INSIDE = 0; // 0000
const int LEFT   = 1; // 0001
const int RIGHT  = 2; // 0010
const int BOTTOM = 4; // 0100
const int TOP    = 8; // 1000

float x_min = 200.0f, y_min = 200.0f, x_max = 600.0f, y_max = 600.0f;

// Función para leer shaders desde archivos
std::string leerShader(const char* ruta) {
    std::ifstream archivo(ruta);
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    return buffer.str();
}

// Algoritmo de Cohen-Sutherland
bool cohenSutherlandClip(float& x0, float& y0, float& x1, float& y1) {
//COMPLETA EL CÓDIGO


}

int main() {
    if (!glfwInit()) return -1;

    // 1. CONFIGURACIÓN CRÍTICA: Indicar que usaremos OpenGL Moderno (Core Profile 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Obligatorio en macOS
#endif

    GLFWwindow* window = glfwCreateWindow(500, 500, "Cohen-Sutherland Modern OpenGL", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 2. CONFIGURACIÓN CRÍTICA: Activar extensiones experimentales antes de glewInit()
    glewExperimental = GL_TRUE; 
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error al inicializar GLEW" << std::endl;
        return -1;
    }

    // Cargar y compilar Shaders
    std::string vShaderStr = leerShader("../vertex_shader.vert");
    std::string fShaderStr = leerShader("../fragment_shader.frag");
    
    // 3. BUENA PRÁCTICA: Validar que el archivo fue leído
    if(vShaderStr.empty() || fShaderStr.empty()) {
        std::cerr << "Error: No se pudieron leer los archivos shader." << std::endl;
        return -1;
    }

    const char* vCode = vShaderStr.c_str();
    const char* fCode = fShaderStr.c_str();

    // Compilación con comprobación de errores básicos
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vCode, NULL);
    glCompileShader(vShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        std::cerr << "Error de compilación Vertex Shader:\n" << infoLog << std::endl;
    }

    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fCode, NULL);
    glCompileShader(fShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);

    // Datos de la línea y el rectángulo
    float lx0 = 100.0f, ly0 = 100.0f, lx1 = 800.0f, ly1 = 800.0f;
    float rectVerts[] = { x_min,y_min,0, x_max,y_min,0, x_max,y_min,0, x_max,y_max,0, 
                          x_max,y_max,0, x_min,y_max,0, x_min,y_max,0, x_min,y_min,0 };

    bool visible = cohenSutherlandClip(lx0, ly0, lx1, ly1);
    float lineVerts[] = { lx0, ly0, 0.0f, lx1, ly1, 0.0f };

    unsigned int VAO[2], VBO[2];
    glGenVertexArrays(2, VAO); 
    glGenBuffers(2, VBO);

    for(int i=0; i<2; ++i) {
        glBindVertexArray(VAO[i]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[i]);
        glBufferData(GL_ARRAY_BUFFER, (i==0 ? sizeof(rectVerts) : sizeof(lineVerts)), (i==0 ? rectVerts : lineVerts), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    // Proyección Ortográfica
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Fondo blanco
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Nota: glLineWidth(3.0f) funcionará solo si tu driver/OS aún tolera la compatibilidad legacy.
        glLineWidth(3.0f);  

        // Dibujar Rectángulo en Rojo
        glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0f, 0.0f, 0.0f);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_LINES, 0, 8);

        // Dibujar Línea Recortada en Azul
        if (visible) {
            glUniform3f(glGetUniformLocation(shaderProgram, "color"), 0.0f, 0.0f, 1.0f);
            glBindVertexArray(VAO[1]);
            glDrawArrays(GL_LINES, 0, 2);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
