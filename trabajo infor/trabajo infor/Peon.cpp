#include "Peon.h"
#include <cmath>
//nati
#include <iostream>

Peon::Peon(bool esBlanco) {
    this->esBlanco = esBlanco;
}

char Peon::obtenerSimbolo() const {
    return esBlanco ? 'P' : 'p';
}

std::string Peon::obtenerNombreClave() const {
    return esBlanco ? "PEONBLANCO_ALV" : "PEONNEGRO_ALV";
}
//CAMBIOSRECIENTE
/*
bool Peon::movimientoValido(int xi, int yi, int xf, int yf, Pieza*** tablero, int filas, int columnas) {
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        return false;
    }

    int dir = esBlanco ? -1 : 1;
    int avanceEsperado = xi + dir;

    // Movimiento hacia adelante
    if (xf == avanceEsperado && yf == yi && tablero[xf][yf] == nullptr)
        return true;

    // Captura en diagonal
    if (xf == avanceEsperado && std::abs(yf - yi) == 1) {
        Pieza* objetivo = tablero[xf][yf];
        //nati
        // Protección adicional: asegurarnos de que el puntero no está dañado
        uintptr_t raw = reinterpret_cast<uintptr_t>(objetivo);
        if (raw == 0xFDFDFDFD || raw == 0xDDDDDDDD || raw == 0xCDCDCDCD || raw == 0 || raw > 0x00007FFFFFFFFFFF)
            return false;
        if (objetivo != nullptr && objetivo->esBlanca() != esBlanco)
            return true;
    }
        return false;
}
    */
bool Peon::movimientoValido(int xi, int yi, int xf, int yf, Pieza* tablero[6][6], int filas, int columnas) {
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        std::cout << "Movimiento fuera de los límites del tablero.\n";
        return false;
    }

    int dir = esBlanco ? -1 : 1;
    int avanceEsperado = xi + dir;

    // Movimiento hacia adelante
    if (xf == avanceEsperado && yf == yi && tablero[xf][yf] == nullptr) {
        std::cout << "Movimiento válido hacia adelante.\n";
        return true;
    }

    // Captura en diagonal
    if (xf == avanceEsperado && std::abs(yf - yi) == 1) {
        Pieza* objetivo = tablero[xf][yf];

        // DEBUG: imprimir puntero destino
        std::cout << "Intentando capturar en [" << xf << "," << yf << "] -> puntero: " << objetivo << "\n";

        if (!objetivo) {
            std::cout << "No hay pieza en la diagonal para capturar.\n";
            return false;
        }

        uintptr_t raw = reinterpret_cast<uintptr_t>(objetivo);
        if (raw == 0xFDFDFDFD || raw == 0xDDDDDDDD || raw == 0xCDCDCDCD || raw == 0 || raw > 0x00007FFFFFFFFFFF) {
            std::cout << "Puntero corrupto detectado en destino. Movimiento inválido.\n";
            return false;
        }

        try {
            char simbolo = objetivo->obtenerSimbolo();  // posible crash aquí
            bool color = objetivo->esBlanca();

            if (color == esBlanco) {
                std::cout << "La pieza en la diagonal es del mismo color. Movimiento inválido.\n";
                return false;
            }

            std::cout << "Captura válida: " << simbolo << std::endl;
            return true;

        }
        catch (...) {
            std::cout << "Excepción atrapada: acceso inválido al capturar.\n";
            return false;
        }
    }

    std::cout << "Movimiento inválido: no coincide con reglas del peón.\n";
    return false;
}
