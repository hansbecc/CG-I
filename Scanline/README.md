# Práctica N° 05: Algoritmo de Relleno de Polígono por Línea de Barrido (Scanline)

Este repositorio contiene la implementación del Algoritmo de Relleno de Polígono por Línea de Barrido (Scanline) utilizando **C++** y **OpenGL**.

## 1. Objetivo
* Analizar casos no triviales de recorte.
* Ejecutar y modificar un ejemplo de relleno de polígonos por Scan-Line.

## 2. Algoritmo Scan Line en OpenGL
El **Scan Line Fill** rellena un polígono recorriendo cada fila horizontal (*scanline*) entre $y_{\text{min}}$ e $y_{\text{max}}$, calculando las intersecciones con sus aristas y coloreando los píxeles entre pares de intersecciones.

> **Nota fundamental:** En OpenGL moderno el relleno lo ejecuta el *hardware*. El `vertex shader` posiciona vértices; el `fragment shader` colorea cada fragmento (píxel) generado automáticamente por el rasterizador, que internamente aplica Scan Line.

## 4. Compilación y Ejecución con CMake

Para compilar este proyecto, asegúrate de tener instaladas las dependencias de OpenGL y sigue estos pasos:

1. **Configurar el proyecto:**
   ```bash
   mkdir build && cd build
   cmake ..

2. **Compilar:**
   ```bash
   cmake --build .
 
3. **Ejecutar:**
   ```bash
   ./scanline
