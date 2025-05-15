#include "Peon.h"
#include <cmath>

Peon::Peon(bool esBlanco) {
    this->esBlanco = esBlanco;
}

char Peon::obtenerSimbolo() const {
    return esBlanco ? 'P' : 'p';
}

std::string Peon::obtenerNombreClave() const {
    return esBlanco ? "PEONBLANCO_ALV" : "PEONNEGRO_ALV";
}


bool Peon::movimientoValido(int xi, int yi, int xf, int yf, Pieza*** tablero, int filas, int columnas) {
    // Verificar límites (¡CRUCIAL!)
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false; // Movimiento fuera del tablero
    }
    int dir = esBlanco ? -1 : 1;

    // Captura en diagonal (permitimos comerse lo que sea)
    if (xf == xi + dir && std::abs(yf - yi) == 1 && tablero[xf][yf] != nullptr)
        return true;

    return false;
}
