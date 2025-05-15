#include "Rey.h"
#include <cmath>

Rey::Rey(bool esBlanco) {
    this->esBlanco = esBlanco;
}

char Rey::obtenerSimbolo() const {
    return esBlanco ? 'R' : 'r';
}
std::string Rey::obtenerNombreClave() const {
    return esBlanco ? "REYBLANCO_ALV" : "REYNEGRO_ALV";
}

bool Rey::movimientoValido(int xi, int yi, int xf, int yf, Pieza*** tablero, int filas, int columnas) {
    // Verificar límites 
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false; // Movimiento fuera del tablero
    }
    int dx = std::abs(xf - xi);
    int dy = std::abs(yf - yi);

    // Movimiento máximo de una casilla en cualquier dirección
    if (dx <= 1 && dy <= 1) {
        return true;  
    }

}

