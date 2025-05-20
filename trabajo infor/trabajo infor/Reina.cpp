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


bool Reina::movimientoValido(int xi, int yi, int xf, int yf, Pieza* tablero[4][4], int filas, int columnas) {
    int dx = std::abs(xf - xi);
    int dy = std::abs(yf - yi);

    // Verificar límites del tablero
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false; // Movimiento fuera del tablero
    }

    // Movimiento recto u en diagonal
    if (dx == dy || xi == xf || yi == yf) {
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
