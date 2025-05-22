#include "Caballo.h"
#include <cmath>


Caballo::Caballo(bool esBlanco) {
    this->esBlanco = esBlanco;
}

char Caballo::obtenerSimbolo() const {
    return esBlanco ? 'C' : 'c';  // C para blanco, c para negro
}
std::string Caballo::obtenerNombreClave() const {
    return esBlanco ? "CABALLOBLANCO_ALV" : "CABALLONEGRO_ALV";
}


bool Caballo::movimientoValido(int xi, int yi, int xf, int yf, Pieza** tablero, int filas, int columnas) {
    // Verificar límites 
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false; // Movimiento fuera del tablero
    }
    int dx = abs(xf - xi);
    int dy = abs(yf - yi);

    // Movimientos en forma de "L"
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        return true; // Permite comerse cualquier pieza, incluso del mismo color
    }
    return false;
}

