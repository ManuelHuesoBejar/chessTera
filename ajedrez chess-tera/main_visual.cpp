#include <GL/glew.h>
#include <GL/glut.h>
#include <map>
#include <string>
#include "Tablero.h"
#include "Tablero_al.h"
#include "Texturas.h"
#include "Rey.h"
#include "Reina.h"
#include "Peon.h"
#include "Caballo.h"
#include "Torre.h"
#include <iostream>
#include "ETSIDI.h"
// Mapa de texturas
std::map<std::string, GLuint> texturas;
Tablero t;
Tablero_al t2;

// Estado de selección
int seleccionX = -1, seleccionY = -1;
bool turnoBlancas = true;  // true = blancas, false = negras

int obtenerFilas(Tablero& tablero) { return 4; }
int obtenerFilas(Tablero_al& tablero) { return 6; }
int obtenerColumnas(Tablero& tablero) { return 4; }
int obtenerColumnas(Tablero_al& tablero) { return 6; }
int opcion;


void cargarTexturas() {
    texturas["PEONBLANCO_ALV"] = cargarTextura("texturas/PEONBLANCO_ALV.png");
    texturas["PEONNEGRO_ALV"] = cargarTextura("texturas/PEONNEGRO_ALV.png");
    texturas["REYBLANCO_ALV"] = cargarTextura("texturas/REYBLANCO_ALV.png");
    texturas["REYNEGRO_ALV"] = cargarTextura("texturas/REYNEGRO_ALV.png");
    texturas["REINABLANCA_ALV"] = cargarTextura("texturas/REINABLANCA_ALV.png");
    texturas["REINANEGRA_ALV"] = cargarTextura("texturas/REINANEGRA_ALV.png");
    texturas["CABALLOBLANCO_ALV"] = cargarTextura("texturas/CABALLOBLANCO_ALV.png");
    texturas["CABALLONEGRO_ALV"] = cargarTextura("texturas/CABALLONEGRO_ALV.png");
    texturas["TORREBLANCA_ALV"] = cargarTextura("texturas/TORREBLANCA_ALV.png");
    texturas["TORRENEGRA_ALV"] = cargarTextura("texturas/TORRENEGRA_ALV.png");
}

void display() {
    /*glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float x = j;
            float y = 3 - i;

            // Casilla base
            if ((i + j) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(0.5f, 0.5f, 0.5f);

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + 1, y);
            glVertex2f(x + 1, y + 1);
            glVertex2f(x, y + 1);
            glEnd();

            // Resaltar pieza seleccionada
            if (i == seleccionX && j == seleccionY) {
                glColor3f(0.0f, 1.0f, 0.0f); // verde
                glLineWidth(3);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x, y);
                glVertex2f(x + 1, y);
                glVertex2f(x + 1, y + 1);
                glVertex2f(x, y + 1);
                glEnd();
            }

            // Pieza (si hay)
            Pieza* pieza = t.obtenerPieza(i, j);
            if (pieza) {
                std::string clave = pieza->obtenerNombreClave();
                if (texturas.count(clave)) {
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[clave]);
                    glColor3f(1, 1, 1);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0, 0); glVertex2f(x, y);
                    glTexCoord2f(1, 0); glVertex2f(x + 1, y);
                    glTexCoord2f(1, 1); glVertex2f(x + 1, y + 1);
                    glTexCoord2f(0, 1); glVertex2f(x, y + 1);
                    glEnd();
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }
    }

    glutSwapBuffers();
}*/
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    int filas, columnas;
    if (opcion == 1) {
        std::cout << "Opcion es 1 (Los Alamos)\n";
        std::cout << "Tipo de t2: " << typeid(t2).name() << std::endl;
        filas = obtenerFilas(t2);
        columnas = obtenerColumnas(t2);
        std::cout << "Filas: " << filas << ", Columnas: " << columnas << std::endl;
    }
    else {
        std::cout << "Opcion es 2 (Silverman)\n";
        std::cout << "Tipo de t: " << typeid(t).name() << std::endl;
        filas = obtenerFilas(t);
        columnas = obtenerColumnas(t);
    }
    std::cout << "Filas: " << filas << ", Columnas: " << columnas << std::endl;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            float x = j;
            float y = filas - 1 - i; 

            // Casilla base
            if ((i + j) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(0.5f, 0.5f, 0.5f);

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + 1, y);
            glVertex2f(x + 1, y + 1);
            glVertex2f(x, y + 1);
            glEnd();

            // Resaltar pieza seleccionada
            if (i == seleccionX && j == seleccionY) {
                glColor3f(0.0f, 1.0f, 0.0f);
                glLineWidth(3);
                glBegin(GL_LINE_LOOP);
                glVertex2f(x, y);
                glVertex2f(x + 1, y);
                glVertex2f(x + 1, y + 1);
                glVertex2f(x, y + 1);
                glEnd();
            }

            // Pieza (si hay)
            Pieza* pieza = (opcion == 1) ? t2.obtenerPieza_al(i, j) : t.obtenerPieza(i, j);
            if (pieza) {
                std::string clave = pieza->obtenerNombreClave();
                if (texturas.count(clave)) {
                    glEnable(GL_TEXTURE_2D);
                    glBindTexture(GL_TEXTURE_2D, texturas[clave]);
                    glColor3f(1, 1, 1);
                    glBegin(GL_QUADS);
                    glTexCoord2f(0, 0); glVertex2f(x, y);
                    glTexCoord2f(1, 0); glVertex2f(x + 1, y);
                    glTexCoord2f(1, 1); glVertex2f(x + 1, y + 1);
                    glTexCoord2f(0, 1); glVertex2f(x, y + 1);
                    glEnd();
                    glDisable(GL_TEXTURE_2D);
                }
            }
        }
    }

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int maxDimension = (opcion == 1) ? 6 : 4;

    gluOrtho2D(0, maxDimension, 0, maxDimension);
    glMatrixMode(GL_MODELVIEW);
}

/*void manejarClic(int fila, int columna) {
    Pieza* piezaClicada = t.obtenerPieza(fila, columna);

    if (seleccionX == -1 && seleccionY == -1) {
        // Primer clic: seleccionar una pieza del turno actual
        if (piezaClicada != nullptr && piezaClicada->esBlanca() == turnoBlancas) {
            seleccionX = fila;
            seleccionY = columna;
            std::cout << "Pieza seleccionada en [" << fila << ", " << columna << "]\n";
            // Aquí podrías añadir alguna retroalimentación visual más directa si es necesario
        }
        else {
            std::cout << "Clic en casilla vacía o pieza del oponente.\n";
            // No hacer nada si se hace clic en una casilla vacía o una pieza del oponente en el primer clic
        }
    }
    else {
        // Segundo clic: intentar mover la pieza seleccionada
        if (fila == seleccionX && columna == seleccionY) {
            // Segundo clic en la misma pieza: deseleccionar
            seleccionX = -1;
            seleccionY = -1;
            std::cout << "Deseleccionada la pieza en [" << fila << ", " << columna << "]\n";
        }
        else {
            std::cout << "Intento de mover desde [" << seleccionX << ", " << seleccionY << "] a [" << fila << ", " << columna << "]\n";
            int resultado = t.moverPieza(seleccionX, seleccionY, fila, columna);
            if (resultado != 0) {
                turnoBlancas = !turnoBlancas; // Cambiar turno si el movimiento fue válido
                std::cout << (turnoBlancas ? "Turno de las blancas.\n" : "Turno de las negras.\n");
            }
            else {
                std::cout << "Movimiento inválido.\n";
                // Aquí podrías añadir alguna retroalimentación visual o de audio sobre el movimiento inválido
            }
            seleccionX = -1;
            seleccionY = -1; // Resetear la selección después del intento de movimiento
        }
    }

    glutPostRedisplay(); // Redibujar la escena para mostrar los cambios
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int ancho = glutGet(GLUT_WINDOW_WIDTH);
        int alto = glutGet(GLUT_WINDOW_HEIGHT);

        // Calcular la columna y la fila basadas en la posición del clic
        int columna = (x * 4) / ancho;
        int fila = 3 - ((y * 4) / alto);

        // Asegurarse de que las coordenadas calculadas estén dentro del tablero (0-3)
        if (fila >= 0 && fila < 4 && columna >= 0 && columna < 4) {
            manejarClic(fila, columna);
        }
        else {
            // Si el clic está fuera del tablero, podrías deseleccionar la pieza
            seleccionX = -1;
            seleccionY = -1;
            glutPostRedisplay(); // Para actualizar la visualización sin selección
        }
    }
}*/



int main(int argc, char** argv) {
    std::cout << "Selecciona variante de ajedrez:\n";
    std::cout << "1. Los Alamos\n";
    std::cout << "2. Silverman 4x4\n";
    std::cout << "Opcion: ";
    std::cin >> opcion;
    std::cout << "Opcion seleccionada: " << opcion << std::endl;

    if (opcion == 1)
        t2.cargarLosAlamos();
    else
        t.cargarSilverman();




    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Tablero 4x4 - Visual");

    glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    cargarTexturas();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
   // glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
