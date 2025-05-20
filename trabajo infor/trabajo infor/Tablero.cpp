#include "Tablero.h"
#include <iostream>
#include "Rey.h"
#include "Reina.h"
#include "Peon.h"
#include "Torre.h"
#include "Caballo.h"


Tablero::Tablero() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            casillas[i][j] = nullptr;
}

Tablero::~Tablero() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            delete casillas[i][j];
}

void Tablero::mostrar() {
    std::cout << "  0 1 2 3\n";
    for (int i = 0; i < 4; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 4; j++) {
            if (casillas[i][j])
                std::cout << casillas[i][j]->obtenerSimbolo() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

void Tablero::colocarPieza(Pieza* pieza, int x, int y) {
    casillas[x][y] = pieza;
}
Pieza* Tablero::obtenerPieza(int x, int y) {
    if (x < 0 || x >= 4 || y < 0 || y >= 4) return nullptr;
    return casillas[x][y];
}
//CAMBIOS RECIENTE
/*
int Tablero::moverPieza(int xi, int yi, int xf, int yf) {
    if (casillas[xi][yi] && casillas[xi][yi]->movimientoValido(xi, yi, xf, yf, (Pieza***)casillas, 4, 4)) {
        // Si hay pieza en destino y es un rey, fin del juego
        if (casillas[xf][yf] != nullptr) {
            char simbolo = casillas[xf][yf]->obtenerSimbolo();
            if (simbolo == 'R' || simbolo == 'r') {
                delete casillas[xf][yf];
                casillas[xf][yf] = casillas[xi][yi];
                casillas[xi][yi] = nullptr;
                return 2; // Rey capturado
            }
        }

        // Movimiento normal
        delete casillas[xf][yf]; // captura si hay algo
        casillas[xf][yf] = casillas[xi][yi];
        casillas[xi][yi] = nullptr;


        Pieza* pieza = casillas[xf][yf];
        if (pieza != nullptr) {
            char simbolo = pieza->obtenerSimbolo();

            // Peón blanco llega a fila 0
            if (simbolo == 'P' && xf == 0) {
                delete casillas[xf][yf];
                casillas[xf][yf] = new Reina(true);
                std::cout << "¡Peón blanco promocionado a Reina!\n";
            }

            // Peón negro llega a fila 3
            else if (simbolo == 'p' && xf == 3) {
                delete casillas[xf][yf];
                casillas[xf][yf] = new Reina(false);
                std::cout << "¡Peón negro promocionado a Reina!\n";
            }
        }

        return 1; // Movimiento válido
    }

    return 0; // Movimiento inválido
}
*/
/*int Tablero::moverPieza(int xi, int yi, int xf, int yf) {
    if (xi < 0 || xi > 3 || yi < 0 || yi > 3 || xf < 0 || xf > 3 || yf < 0 || yf > 3) {
        return 0; // Movimiento fuera del tablero
    }

    if (!this->Tablero[xi][yi]) {  // Corregido: usar this->
        return 0; // No hay pieza en la casilla de origen
    }

    if (!this->Tablero[xi][yi]->movimientoValido(xi, yi, xf, yf, this->Tablero)) { // Corregido: usar this->
        return 0; // Movimiento inválido para la pieza
    }

    // Si hay una pieza en la casilla de destino y es del oponente, "captúrala" (reemplázala)
    // No necesitamos eliminarla explícitamente en este caso, simplemente la reemplazamos

    // Mover la pieza desde el origen al destino
    this->Tablero[xf][yf] = this->Tablero[xi][yi]; // Corregido: usar this->
    this->Tablero[xi][yi] = nullptr;       // Corregido: usar this->

    return 1; // Movimiento exitoso
}*/


// ✅ ESTA FUNCIÓN DEBE ESTAR FUERA DE moverPieza
/*void Tablero::cargarLosAlamos() {
    // Limpiar tablero
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }

    // Negras (arriba)
    casillas[0][0] = new Rey(false);
    casillas[0][1] = new Reina(false);
    casillas[0][2] = new Alfil(false);
    casillas[0][3] = new Peon(false);

    // Blancas (abajo)
    casillas[3][0] = new Peon(true);
    casillas[3][1] = new Alfil(true);
    casillas[3][2] = new Reina(true);
    casillas[3][3] = new Rey(true);
}
Pieza* Tablero::obtenerPieza(int x, int y) {
        if (x < 0 || x >= 4 || y < 0 || y >= 4) return nullptr;
        return casillas[x][y];
}*/
//CAMBIOS RECIENTE
int Tablero::moverPieza(int xi, int yi, int xf, int yf) {
    std::cout << "Estado del tablero antes de mover:\n";
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << "[" << i << "][" << j << "] = " << casillas[i][j] << "  ";
        }
        std::cout << "\n";
    }

    if (xi < 0 || xi >= 4 || yi < 0 || yi >= 4 || xf < 0 || xf >= 4 || yf < 0 || yf >= 4)
        return 0;

    Pieza* origen = casillas[xi][yi];
    Pieza* destino = casillas[xf][yf];

    std::cout << "Origen [" << xi << "," << yi << "] = " << origen << "\n";
    std::cout << "Destino [" << xf << "," << yf << "] = " << destino << "\n";

    if (!origen) return 0;
    
    if (!origen->movimientoValido(xi, yi, xf, yf, casillas, 4, 4))
        return 0;

    // Captura al rey (fin del juego)
    if (destino != nullptr) {
        char simbolo = destino->obtenerSimbolo();
        if (simbolo == 'R' || simbolo == 'r') {
            delete destino;
            casillas[xf][yf] = nullptr;
            casillas[xf][yf] = origen;
            casillas[xi][yi] = nullptr;
            return 2;
        }

        // Captura normal
        delete destino;
        casillas[xf][yf] = nullptr;
    }

    // Movimiento normal
    casillas[xf][yf] = origen;
    casillas[xi][yi] = nullptr;

    // Promoción
    char simbolo = origen->obtenerSimbolo();
    if (simbolo == 'P' && xf == 0) {
        delete casillas[xf][yf];
        casillas[xf][yf] = nullptr;
        casillas[xf][yf] = new Reina(true);
    }
    else if (simbolo == 'p' && xf == 3) {
        delete casillas[xf][yf];
        casillas[xf][yf] = nullptr;
        casillas[xf][yf] = new Reina(false);
    }

    std::cout << "Movimiento realizado [" << xi << "," << yi << "] -> [" << xf << "," << yf << "]\n";
    return 1;
}


void Tablero::cargarSilverman() {
    // Limpiar tablero
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }

    // FILA 0 (negras arriba): TORRE, REINA, REINA, TORRE
    casillas[0][0] = new Torre(false);
    casillas[0][1] = new Rey(false);
    casillas[0][2] = new Reina(false);
    casillas[0][3] = new Torre(false);

    // FILA 1 (peones negros)
    for (int j = 0; j < 4; ++j)
        casillas[1][j] = new Peon(false);

    // FILA 2 (peones blancos)
    for (int j = 0; j < 4; ++j)
        casillas[2][j] = new Peon(true);

    // FILA 3 (blancas abajo): TORRE, REINA, REINA, TORRE
    casillas[3][0] = new Torre(true);
    casillas[3][2] = new Reina(true);
    casillas[3][1] = new Rey(true);
    casillas[3][3] = new Torre(true);
}
