#include <GL/glew.h>   
#include <GL/glut.h>   
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


GLuint cargarTextura(const char* ruta) {
    int ancho, alto, canales;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(ruta, &ancho, &alto, &canales, 0);

    if (!data) {
        std::cerr << "No se pudo cargar la imagen: " << ruta << std::endl;
        return 0;
    }

    GLuint texturaID;
    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    GLenum formato = (canales == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, formato, ancho, alto, 0, formato, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    return texturaID;
}
