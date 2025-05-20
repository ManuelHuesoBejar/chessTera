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



bool Torre::movimientoValido(int xi, int yi, int xf, int yf, Pieza* tablero[4][4], int filas, int columnas) {
    // Verificar límites 
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false; // Movimiento fuera del tablero
    }
    return (xi == xf || yi == yf); 
}
