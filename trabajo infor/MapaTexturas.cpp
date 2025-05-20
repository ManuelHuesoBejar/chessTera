#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>

#include "MapaTexturas.h"
#include "Texturas.h"

std::map<std::string, GLuint> mapaTexturas;


void cargarTodasLasTexturas() {
   /* mapaTexturas["CABALLOBLANCO_ALV"] = cargarTextura("texturas/CABALLOBLANCO_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: CABALLOBLANCO_ALV\n";
    mapaTexturas["CABALLONEGRO_ALV"] = cargarTextura("texturas/CABALLONEGRO_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: CABALLONEGRO_ALV\n";
    mapaTexturas["PEONBLANCO_ALV"] = cargarTextura("texturas/PEONBLANCO_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: PEONBLANCO_ALV\n";
    mapaTexturas["PEONNEGRO_ALV"] = cargarTextura("texturas/PEONNEGRO_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: PEONNEGRO_ALV\n";
    mapaTexturas["REINABLANCA_ALV"] = cargarTextura("texturas/REINABLANCA_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: REINABLANCA_ALV\n";
    mapaTexturas["REINANEGRA_ALV"] = cargarTextura("texturas/REINANEGRA_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: REINANEGRA_ALV\n";
    mapaTexturas["REYBLANCO_ALV"] = cargarTextura("texturas/REYBLANCO_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: REYBLANCO_ALV\n";
    mapaTexturas["REYNEGRO_ALV"] = cargarTextura("texturas/REYNEGRO_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: REYNEGRO_ALV\n";
    mapaTexturas["TORREBLANCA_ALV"] = cargarTextura("texturas/TORREBLANCA_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: TORREBLANCA_ALV\n";
    mapaTexturas["TORRENEGRA_ALV"] = cargarTextura("texturas/TORRENEGRA_ALV.png");
    std::cout << "cargarTexturas(): Insertada clave: TORRENEGRA_ALV\n";*/
    mapaTexturas["PEONBLANCO_ALV"] = cargarTextura("texturas/PEONBLANCO_ALV.png");
    mapaTexturas["PEONNEGRO_ALV"] = cargarTextura("texturas/PEONNEGRO_ALV.png");
    mapaTexturas["REYBLANCO_ALV"] = cargarTextura("texturas/REYBLANCO_ALV.png");
    mapaTexturas["REYNEGRO_ALV"] = cargarTextura("texturas/REYNEGRO_ALV.png");
    mapaTexturas["REINABLANCA_ALV"] = cargarTextura("texturas/REINABLANCA_ALV.png");  // Corregido
    mapaTexturas["REINANEGRA_ALV"] = cargarTextura("texturas/REINANEGRA_ALV.png");  // Corregido
    mapaTexturas["CABALLOBLANCO_ALV"] = cargarTextura("texturas/CABALLOBLANCO_ALV.png");
    mapaTexturas["CABALLONEGRO_ALV"] = cargarTextura("texturas/CABALLONEGRO_ALV.png");
    mapaTexturas["TORREBLANCA_ALV"] = cargarTextura("texturas/TORREBLANCA_ALV.png");  // Corregido
    mapaTexturas["TORRENEGRA_ALV"] = cargarTextura("texturas/TORRENEGRA_ALV.png");  // Corregido
}
