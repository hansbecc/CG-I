# Práctica N° 04: Algoritmo de Recorte de Líneas de Cohen-Sutherland

Este repositorio contiene la implementación del algoritmo de recorte de líneas de **Cohen-Sutherland** utilizando **C++** y **OpenGL**.

## 1. Objetivo
* Conocer el algoritmo de recorte de líneas de Cohen-Sutherland.
* Implementar el algoritmo de Cohen-Sutherland en OpenGL.

## 2. Descripción del Algoritmo
El algoritmo realiza comprobaciones iniciales para evitar cálculos innecesarios de intersecciones. Se basa en la asignación de un código de 4 bits (b3b2b1b0) a cada región del plano respecto al rectángulo de recorte:

* **Bit 0 (LEFT):** Izquierda.
* **Bit 1 (RIGHT):** Derecha.
* **Bit 2 (BOTTOM):** Abajo.
* **Bit 3 (TOP):** Arriba.

### Proceso de Recorte
1. Se comprueba si los puntos extremos son aceptados por sus posiciones.
2. Si no es posible la aceptación/rechazo inmediato, se divide el segmento por una arista del rectángulo de recorte.
3. El proceso es iterativo hasta que el segmento sea aceptado o rechazado.

## 3. Estructura del Código
El proyecto implementa las siguientes funciones principales descritas en la práctica:
* `ComputeOutCode`: Calcula el código de región para un punto $(x, y)$ dado.
* `CohenSutherlandClip`: Ejecuta el bucle de recorte, cálculo de intersecciones y renderizado final.

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
   ./CohenSutherland


