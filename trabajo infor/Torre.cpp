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



bool Torre::movimientoValido(int xi, int yi, int xf, int yf, Pieza* tablero[6][6], int filas, int columnas) {
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false;
    }

    if (xi == xf) {
        int step = (yf > yi) ? 1 : -1;
        for (int i = 1; i < abs(yf - yi); i++) {
            if (tablero[xi][yi + i * step] != nullptr)
                return false;
        }
        return true;
    }

    if (yi == yf) {
        int step = (xf > xi) ? 1 : -1;
        for (int i = 1; i < abs(xf - xi); i++) {
            if (tablero[xi + i * step][yi] != nullptr)
                return false;
        }
        return true;
    }

    return false;
}
