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
// Mapa de texturas
std::map<std::string, GLuint> texturas;
Tablero t;
Tablero_al t2;

// Estado de selección
int seleccionX = -1, seleccionY = -1;
bool turnoBlancas = true;  // true = blancas, false = negras
bool gameOver = false;
bool ganadorBlancas = false;

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
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    int filas, columnas;
    if (opcion == 1) {
        filas = obtenerFilas(t2);
        columnas = obtenerColumnas(t2);
    }
    else {
        filas = obtenerFilas(t);
        columnas = obtenerColumnas(t);
    }

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
    if (gameOver) {
        // Capa semitransparente
        glColor4f(0, 0, 0, 0.6f);
        glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(columnas, 0);
        glVertex2f(columnas, filas);
        glVertex2f(0, filas);
        glEnd();

        // Texto “Fin de la partida” y ganador
        std::string mensaje1 = "¡Fin de la partida!";
        std::string mensaje2 = ganadorBlancas ? "Ganan las Blancas" : "Ganan las Negras";

        glColor3f(1, 1, 1);
        glRasterPos2f(columnas / 2 - 2.5f, filas / 2 + 0.5f);
        for (char c : mensaje1) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

        glRasterPos2f(columnas / 2 - 2.0f, filas / 2 - 0.5f);
        for (char c : mensaje2) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
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

void manejarClic(int fila, int columna) {
    if (gameOver) return;

    Pieza* piezaClicada = (opcion == 1)
        ? t2.obtenerPieza_al(fila, columna)
        : t.obtenerPieza(fila, columna);

    if (seleccionX == -1 && seleccionY == -1) {
        if (piezaClicada && piezaClicada->esBlanca() == turnoBlancas) {
            seleccionX = fila;
            seleccionY = columna;
            std::cout << "Pieza seleccionada en ["
                << fila << "," << columna << "]\n";
        }
        else {
            std::cout << "Clic en casilla vacia o pieza del oponente.\n";
        }
        return;
    }

    if (fila == seleccionX && columna == seleccionY) {
        seleccionX = seleccionY = -1;
        std::cout << "Deseleccionada la pieza en ["
            << fila << "," << columna << "]\n";
        return;
    }

    std::cout << "Intento de mover desde ["
        << seleccionX << "," << seleccionY
        << "] a [" << fila << "," << columna << "]\n";

    // 1) Ejecutar movimiento
    int resultado = (opcion == 1)
        ? t2.moverPieza_al(seleccionX, seleccionY, fila, columna)
        : t.moverPieza(seleccionX, seleccionY, fila, columna);

    if (resultado == 0) {
        std::cout << "Movimiento invalido.\n";
        seleccionX = seleccionY = -1;
        return;
    }

    // 2) ¿He capturado al rey rival?
    if (resultado == 2) {
        gameOver = true;
        ganadorBlancas = turnoBlancas;
    }
    else {
        // 3) ¿Ha quedado mi oponente en jaque mate?
        bool oponenteEnMate = (opcion == 1)
            ? t2.esJaqueMate(!turnoBlancas)
            : t.esJaqueMate(!turnoBlancas);

        if (oponenteEnMate) {
            gameOver = true;
            ganadorBlancas = turnoBlancas;
        }
        else {
            // 4) Nada extraordinario: paso turno
            turnoBlancas = !turnoBlancas;
            std::cout << (turnoBlancas
                ? "Turno de las blancas.\n"
                : "Turno de las negras.\n");
        }
    }

    // Reset selección y refrescar pantalla
    seleccionX = seleccionY = -1;
    glutPostRedisplay();
}
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        int ancho = glutGet(GLUT_WINDOW_WIDTH);
        int alto = glutGet(GLUT_WINDOW_HEIGHT);
        int dimension = (opcion == 1) ? 6 : 4;

        // Calcular la columna y la fila basadas en la posición del clic
        int columna = (x * dimension) / ancho;
        int fila = ((y * dimension) / alto);

        // Asegurarse de que las coordenadas calculadas estén dentro del tablero (0-3)
        if (fila >= 0 && fila < dimension && columna >= 0 && columna < dimension) {
            manejarClic(fila, columna);
        }
        else {
            // Si el clic está fuera del tablero, podrías deseleccionar la pieza
            seleccionX = -1;
            seleccionY = -1;
            glutPostRedisplay(); // Para actualizar la visualización sin selección
        }
    }
}



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
    glutCreateWindow("Tablero - Visual");

    glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    cargarTexturas();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
