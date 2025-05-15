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
       // std::cout << "Filas: " << filas << ", Columnas: " << columnas << std::endl;
    }
    else {
        std::cout << "Opcion es 2 (Silverman)\n";
        std::cout << "Tipo de t: " << typeid(t).name() << std::endl;
        filas = obtenerFilas(t);
        columnas = obtenerColumnas(t);
    }
   // std::cout << "Filas: " << filas << ", Columnas: " << columnas << std::endl;

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

void manejarClic(int fila, int columna) {
    Pieza* piezaClicada = t.obtenerPieza(fila, columna);
    Pieza* piezaClicada_al = t2.obtenerPieza_al(fila, columna);
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
}
/*void manejarClic(int fila, int columna) {
    std::cout << "Click en fila: " << fila << ", columna: " << columna << std::endl;

    // Determinar qué tablero está activo
    Pieza* (Tablero:: * obtenerPiezaFunc)(int, int) = nullptr;
    int (Tablero:: * moverPiezaFunc)(int, int, int, int) = nullptr;
    int filas_tablero, columnas_tablero;

    if (opcion == 1) { // Los Alamos
        obtenerPiezaFunc = (Pieza * (Tablero::*)(int, int)) & Tablero_al::obtenerPieza_al;
        moverPiezaFunc = (int (Tablero::*)(int, int, int, int)) & Tablero_al::moverPieza_al;
        filas_tablero = obtenerFilas(t2); // Usa la función que retorna las filas/columnas del tablero_al
        columnas_tablero = obtenerColumnas(t2);
    }
    else { // Silverman 4x4
        obtenerPiezaFunc = &Tablero::obtenerPieza;
        moverPiezaFunc = &Tablero::moverPieza;
        filas_tablero = obtenerFilas(t); // Usa la función que retorna las filas/columnas del tablero
        columnas_tablero = obtenerColumnas(t);
    }

    if (seleccionX == -1) { // No hay pieza seleccionada, intentamos seleccionar una
        Pieza* piezaSeleccionada = nullptr;
        if (opcion == 1) {
            piezaSeleccionada = (t2.*obtenerPiezaFunc)(fila, columna);
        }
        else {
            piezaSeleccionada = (t.*obtenerPiezaFunc)(fila, columna);
        }

        if (piezaSeleccionada != nullptr && piezaSeleccionada->esBlanca() == turnoBlancas) {
            seleccionX = fila;
            seleccionY = columna;
            std::cout << "Pieza seleccionada en: (" << seleccionX << ", " << seleccionY << ") -> " << piezaSeleccionada->obtenerSimbolo() << std::endl;
        }
        else {
            std::cout << "Casilla vacia o pieza del oponente. No se selecciona nada." << std::endl;
        }
    }
    else { // Ya hay una pieza seleccionada, intentamos moverla
        int xi = seleccionX;
        int yi = seleccionY;
        int xf = fila;
        int yf = columna;

        std::cout << "Intentando mover de (" << xi << ", " << yi << ") a (" << xf << ", " << yf << ")" << std::endl;

        int resultado_movimiento = 0;
        if (opcion == 1) {
            resultado_movimiento = (t2.*moverPiezaFunc)(xi, yi, xf, yf);
        }
        else {
            resultado_movimiento = (t.*moverPiezaFunc)(xi, yi, xf, yf);
        }

        if (resultado_movimiento == 1) {
            std::cout << "Movimiento valido." << std::endl;
            turnoBlancas = !turnoBlancas; // Cambiar turno si el movimiento fue exitoso
        }
        else if (resultado_movimiento == 2) {
            std::cout << "¡REY CAPTURADO! FIN DEL JUEGO." << std::endl;
            // Aquí podrías añadir lógica para terminar el juego
        }
        else {
            std::cout << "Movimiento invalido." << std::endl;
        }

        // Deseleccionar la pieza después de intentar el movimiento
        seleccionX = -1;
        seleccionY = -1;
    }
    glutPostRedisplay(); // Solicitar un redibujado de la ventana
}*/

// ... (resto del código) ...

void OnMouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Obtenemos el tamaño actual de la ventana
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int ancho = viewport[2];
        int alto = viewport[3];

        int filas_tablero, columnas_tablero;
        if (opcion == 1) { // Los Alamos
            filas_tablero = obtenerFilas(t2);
            columnas_tablero = obtenerColumnas(t2);
        }
        else { // Silverman 4x4
            filas_tablero = obtenerFilas(t);
            columnas_tablero = obtenerColumnas(t);
        }

        // Calcular la columna y la fila basadas en la posición del clic
        // Importante: la coordenada Y en GLUT va de arriba a abajo, en el tablero de abajo a arriba
        // Necesitas ajustar el mapeo según cómo hayas dibujado tu tablero.
        // Si tu tablero se dibuja de (0,0) abajo a la izquierda y (N,M) arriba a la derecha:
        // fila = (alto - y) * filas_tablero / alto; // Si y=0 es arriba, y=alto es abajo
        // columna = x * columnas_tablero / ancho;

        // Considerando tu código actual donde la fila 0 parece estar arriba (casillas[0][0] = negras)
        // y se dibuja con texturas que asumen 0,0 arriba-izquierda, la conversión debe ser cuidadosa.
        // Asumiendo que tu dibujado de tablero en display() ya considera el eje Y invertido:
        // Si Y en OpenGL es de abajo hacia arriba y tu tablero se dibuja con la fila 0 en la parte superior de la pantalla,
        // entonces el mapeo de Y del ratón (donde 0 es arriba) a la fila del tablero es directo o necesita una inversión simple.

        // Por ejemplo, si tu tablero se dibuja del (0,0) superior-izquierda al (N-1, M-1) inferior-derecha,
        // que es común para matrices, y tu glut ventana tiene (0,0) superior-izquierda:
        int columna = (x * columnas_tablero) / ancho;
        int fila = (y * filas_tablero) / alto;
        // Si tu tablero está dibujado de forma que la fila 0 es la de abajo, entonces necesitas invertir la fila:
        // fila = filas_tablero - 1 - ((y * filas_tablero) / alto);


        // Ajusta esta línea según cómo dibujes tu tablero.
        // Si tu `display()` dibuja la fila 0 en la parte superior y la fila `N-1` en la inferior,
        // y tu ratón `y` también es 0 en la parte superior, entonces:
        // int fila = (y * filas_tablero) / alto;
        // int columna = (x * columnas_tablero) / ancho;
        // Si tu `display()` dibuja la fila 0 en la parte inferior y la fila `N-1` en la superior,
        // y tu ratón `y` es 0 en la parte superior, entonces:
        // int fila = filas_tablero - 1 - ((y * filas_tablero) / alto);
        // int columna = (x * columnas_tablero) / ancho;

        // Basado en tu `main_visual.cpp` y la función `manejarClic` que ya tenías comentada,
        // donde se usa `3 - ((y * 4) / alto)` para el tablero 4x4, esto sugiere que la fila 0
        // del tablero es la de abajo en la pantalla (y la fila 3 la de arriba).
        // Vamos a mantener esa lógica y generalizarla.

        fila = (filas_tablero - 1) - ((y * filas_tablero) / alto);
        columna = (x * columnas_tablero) / ancho;


        // Asegurarse de que las coordenadas calculadas estén dentro de los límites del tablero
        if (fila >= 0 && fila < filas_tablero && columna >= 0 && columna < columnas_tablero) {
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
    glutCreateWindow("Tablero 4x4 - Visual");

    glewInit();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);

    cargarTexturas();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutMouseFunc(mouse);

    glutMainLoop();

    return 0;
}
