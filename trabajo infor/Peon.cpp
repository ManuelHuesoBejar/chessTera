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

bool Peon::movimientoValido(int xi, int yi, int xf, int yf, Pieza** tablero, int filas, int columnas) {
    if (xi < 0 || xi >= filas || yi < 0 || yi >= columnas ||
        xf < 0 || xf >= filas || yf < 0 || yf >= columnas) {
        std::cout << "Movimiento fuera de los límites del tablero.\n";
        return false;
    }

    if (xi == xf && yi == yf) {
        // Si la casilla origen y destino coinciden, no es un movimiento válido
        return false;
    }

    int dir = esBlanco ? -1 : 1;
    int avanceEsperado = xi + dir;

    // Movimiento hacia adelante
    if (xf == avanceEsperado && yf == yi && tablero[xf * columnas + yf] == nullptr) {
        //std::cout << "Movimiento válido hacia adelante.\n";
        return true;
    }

    // Captura en diagonal
    if (xf == avanceEsperado && std::abs(yf - yi) == 1) {
        Pieza* pieza = tablero[xf * columnas + yf];

        // DEBUG: imprimir puntero destino
        //std::cout << "Intentando capturar en [" << xf << "," << yf << "] -> puntero: " << pieza << "\n";

        if (!pieza) {
            //std::cout << "No hay pieza en la diagonal para capturar.\n";
            return false;
        }

        uintptr_t raw = reinterpret_cast<uintptr_t>(pieza);
        if (raw == 0xFDFDFDFD || raw == 0xDDDDDDDD || raw == 0xCDCDCDCD || raw == 0 || raw > 0x00007FFFFFFFFFFF) {
            //std::cout << "Puntero corrupto detectado en destino. Movimiento inválido.\n";
            return false;
        }

        try {
            char simbolo = pieza->obtenerSimbolo();  // posible crash aquí
            bool color = pieza->esBlanca();

            if (color == esBlanco) {
                if ((esBlanco && simbolo == 'R') || (!esBlanco && simbolo == 'r')) {
                    return false;
                }
                // Si es otra pieza propia distinta del rey, permitimos “comerla”
                return true;
            }

            //std::cout << "Captura válida: " << simbolo << std::endl;
            return true;

        }
        catch (...) {
            //std::cout << "Excepción atrapada: acceso inválido al capturar.\n";
            return false;
        }
    }

    //std::cout << "Movimiento inválido: no coincide con reglas del peón.\n";
    return false;
}
