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

    if (xi == xf && yi == yf) {
        // Si la casilla origen y destino coinciden, no es un movimiento válido
        return false;
    }

    int dx = abs(xf - xi);
    int dy = abs(yf - yi);

    // Movimientos en forma de "L"
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        Pieza* destino = tablero[xf * columnas + yf];
        if (destino) {
            char s = destino->obtenerSimbolo();
            // Si es rey blanco y este caballo también es blanco → false
            if (esBlanco && s == 'R')
                return false;
            // Si es rey negro y este caballo es negro → false
            if (!esBlanco && s == 'r')
                return false;
        }
        return true; // Permite comerse cualquier pieza, incluso del mismo color
    }
    return false;
}

