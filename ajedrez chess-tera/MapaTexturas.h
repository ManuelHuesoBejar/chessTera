#ifndef MAPA_TEXTURAS_H
#define MAPA_TEXTURAS_H
#include <GL/glew.h>
#include <GL/glut.h>
#include <map>
#include <string>


// Mapa global para almacenar las texturas cargadas
extern std::map<std::string, GLuint> mapaTexturas;

// Función para cargar todas las texturas
void cargarTodasLasTexturas();

#endif
