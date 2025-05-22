#include "Reina.h"
#include <cmath>

Reina::Reina(bool esBlanco) {
    this->esBlanco = esBlanco;
}

char Reina::obtenerSimbolo() const {
    return esBlanco ? 'Q' : 'q';
}
std::string Reina::obtenerNombreClave() const {
    return esBlanco ? "REINABLANCA_ALV" : "REINANEGRA_ALV";
}


bool Reina::movimientoValido(int xi, int yi, int xf, int yf, Pieza** tablero, int filas, int columnas) {
    int dx = xf - xi;
    int dy = yf - yi;

    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false;
    }

    // Movimiento diagonal
    if (abs(dx) == abs(dy)) {
        int stepX = (dx > 0) ? 1 : -1;
        int stepY = (dy > 0) ? 1 : -1;
        for (int i = 1; i < abs(dx); i++) {
            int fila = xi + i * stepX;
            int columna = yi + i * stepY;
            if (tablero[fila * columnas + columna] != nullptr)
                return false; // Obstáculo en el camino
        }
        return true;
    }

    // Movimiento horizontal
    if (yi == yf) {
        int step = (dx > 0) ? 1 : -1;
        for (int i = 1; i < abs(dx); i++) {
            int fila = xi + i * step;
            if (tablero[fila * columnas + yi] != nullptr)
                return false;
        }
        return true;
    }

    // Movimiento vertical
    if (xi == xf) {
        int step = (dy > 0) ? 1 : -1;
        for (int i = 1; i < abs(dy); i++) {
            int columna = yi + i * step;
            if (tablero[xi * columnas + columna] != nullptr)
                return false;
        }
        return true;
    }

    return false;
}


/*int dx = std::abs(xf - xi);
int dy = std::abs(yf - yi);

// Movimiento recto u en diagonal
if (dx == dy || xi == xf || yi == yf) {
    return true;
}
return false;
}*/
