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

bool inMenu = true;
int filasTablero = 0, columnasTablero = 0;
int windowWidth = 400, windowHeight = 400;

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
    // Si seguimos en pantalla de menú, dibujamos el menú y nos vamos:
    if (inMenu) {
        // Desactivamos texturas para dibujar solo con color sólido
        glDisable(GL_TEXTURE_2D);
        // PINTAR FONDO OSCURO
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Calculamos tamaño de botones en píxeles
        int btnW = windowWidth / 2;
        int btnH = windowHeight / 8;

        // Botón 1: “Los Alamos”
        int btn1_x = (windowWidth - btnW) / 2;
        int btn1_y = (int)(windowHeight * 0.55f);
        glColor3f(0.8f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2i(btn1_x, btn1_y);
        glVertex2i(btn1_x + btnW, btn1_y);
        glVertex2i(btn1_x + btnW, btn1_y + btnH);
        glVertex2i(btn1_x, btn1_y + btnH);
        glEnd();

        // Texto centrado en botón 1
        glColor3f(1.0f, 1.0f, 1.0f);
        std::string texto1 = "Jugar Los Alamos";
        int text1_w = glutBitmapLength(
            GLUT_BITMAP_HELVETICA_18,
            reinterpret_cast<const unsigned char*>(texto1.c_str()));
        int text1_x = btn1_x + (btnW - text1_w) / 2;
        int text1_y = btn1_y + (btnH + 12) / 2;
        glRasterPos2i(text1_x, text1_y);
        for (char c : texto1)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

        // Botón 2: “Silverman 4x4”
        int btn2_x = (windowWidth - btnW) / 2;
        int btn2_y = (int)(windowHeight * 0.30f);
        glColor3f(0.2f, 0.2f, 0.8f);
        glBegin(GL_QUADS);
        glVertex2i(btn2_x, btn2_y);
        glVertex2i(btn2_x + btnW, btn2_y);
        glVertex2i(btn2_x + btnW, btn2_y + btnH);
        glVertex2i(btn2_x, btn2_y + btnH);
        glEnd();

        // Texto centrado en botón 2
        glColor3f(1.0f, 1.0f, 1.0f);
        std::string texto2 = "Jugar Silverman 4x4";
        int text2_w = glutBitmapLength(
            GLUT_BITMAP_HELVETICA_18,
            reinterpret_cast<const unsigned char*>(texto2.c_str()));
        int text2_x = btn2_x + (btnW - text2_w) / 2;
        int text2_y = btn2_y + (btnH + 12) / 2;
        glRasterPos2i(text2_x, text2_y);
        for (char c : texto2)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);

        glutSwapBuffers();
        return;
    }

    // ——— Si llegamos aquí, inMenu == false, dibujamos tu código ORIGINAL ———
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
                glColor3f(0.0f, 1.0f, 1.0f);
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
    // == AÑADIDO: guardar nuevo tamaño de ventana
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (inMenu) {
        // Mientras esté el menú, trabajamos en coordenadas de píxeles (0..w, 0..h)
        gluOrtho2D(0, w, 0, h);
    }
    else {
        // Una vez elegida la variante, volvemos a coordenadas de tablero
        int maxDimension = std::max(filasTablero, columnasTablero);
        gluOrtho2D(0, maxDimension, 0, maxDimension);
    }
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
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN) return;

    if (inMenu) {
        // Estamos en pantalla de menú: interpretamos (x,y) en pixeles
        int y_invertido = windowHeight - y;
        int btnW = windowWidth / 2;
        int btnH = windowHeight / 8;
        int btn1_x = (windowWidth - btnW) / 2;
        int btn1_y = (int)(windowHeight * 0.55f);
        int btn2_x = (windowWidth - btnW) / 2;
        int btn2_y = (int)(windowHeight * 0.30f);

        // Clic dentro del botón “Los Alamos”?
        if (x >= btn1_x && x <= btn1_x + btnW &&
            y_invertido >= btn1_y && y_invertido <= btn1_y + btnH) {
            // Elegido Los Alamos
            opcion = 1;
            inMenu = false;
            t2.cargarLosAlamos();
            filasTablero = obtenerFilas(t2);
            columnasTablero = obtenerColumnas(t2);
            cargarTexturas();
            reshape(windowWidth, windowHeight);
            glutPostRedisplay();
        }
        // Clic dentro del botón “Silverman 4x4”?
        else if (x >= btn2_x && x <= btn2_x + btnW &&
            y_invertido >= btn2_y && y_invertido <= btn2_y + btnH) {
            // Elegido Silverman 4x4
            opcion = 2;
            inMenu = false;
            t.cargarSilverman();
            filasTablero = obtenerFilas(t);
            columnasTablero = obtenerColumnas(t);
            cargarTexturas();
            reshape(windowWidth, windowHeight);
            glutPostRedisplay();
        }
        // Si clic fuera de los botones, no hacemos nada (seguimos en menú)
    }
    else {
       
        int ancho = glutGet(GLUT_WINDOW_WIDTH);
        int alto = glutGet(GLUT_WINDOW_HEIGHT);
        int dimension = (opcion == 1) ? 6 : 4;
        //int y_inv = alto - y;
        int columna = (x * dimension) / ancho;
        int fila = (y * dimension) / alto;

        if (fila >= 0 && fila < dimension && columna >= 0 && columna < dimension) {
            manejarClic(fila, columna);
        }
        else {
            seleccionX = -1;
            seleccionY = -1;
            glutPostRedisplay();
        }
    }
}


int main(int argc, char** argv) {
    //std::cout << "Selecciona variante de ajedrez:\n";
    //std::cout << "1. Los Alamos\n";
    //std::cout << "2. Silverman 4x4\n";
    //std::cout << "Opcion: ";
    //std::cin >> opcion;
    //std::cout << "Opcion seleccionada: " << opcion << std::endl;
    //
    //if (opcion == 1)
    //    t2.cargarLosAlamos();
    //else
    //
    //    t.cargarSilverman();




    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Tablero - Visual");

    glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    cargarTexturas();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    reshape(windowWidth, windowHeight);

    glutMainLoop();

    return 0;
}
