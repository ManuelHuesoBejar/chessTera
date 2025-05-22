#include "Torre.h"
#include <cmath>

Torre::Torre(bool esBlanco) {
    this->esBlanco = esBlanco;
}

char Torre::obtenerSimbolo() const {
    return esBlanco ? 'T' : 't';
}
std::string Torre::obtenerNombreClave() const {
    return esBlanco ? "TORREBLANCA_ALV" : "TORRENEGRA_ALV";
}



bool Torre::movimientoValido(int xi, int yi, int xf, int yf, Pieza** tablero, int filas, int columnas) {
    int dx = xf - xi;
    int dy = yf - yi;
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