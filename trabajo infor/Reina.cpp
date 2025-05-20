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


bool Reina::movimientoValido(int xi, int yi, int xf, int yf, Pieza* tablero[6][6], int filas, int columnas) {
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
            if (tablero[xi + i * stepX][yi + i * stepY] != nullptr)
                return false; // Obstáculo en el camino
        }
        return true;
    }

    // Movimiento horizontal
    if (yi == yf) {
        int step = (dx > 0) ? 1 : -1;
        for (int i = 1; i < abs(dx); i++) {
            if (tablero[xi + i * step][yi] != nullptr)
                return false;
        }
        return true;
    }

    // Movimiento vertical
    if (xi == xf) {
        int step = (dy > 0) ? 1 : -1;
        for (int i = 1; i < abs(dy); i++) {
            if (tablero[xi][yi + i * step] != nullptr)
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
