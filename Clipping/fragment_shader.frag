#version 330 core
out vec4 FragColor;
uniform vec3 color;

void main() {
    // Establece el color de la línea (Rojo para el recorte, Azul para el resultado) 
    FragColor = vec4(color, 1.0);
}