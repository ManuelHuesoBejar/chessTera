#include "Tablero_al.h"
#include <iostream>
#include "Rey.h"
#include "Reina.h"
#include "Peon.h"
#include "Torre.h"
#include "Caballo.h"


Tablero_al::Tablero_al() {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            casillas[i][j] = nullptr;
}

Tablero_al::~Tablero_al() {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            delete casillas[i][j];
}

void Tablero_al::mostrar_al() {
    std::cout << "  0 1 2 3 4 5\n";
    for (int i = 0; i < 6; i++) {
        std::cout << i << " ";
        for (int j = 0; j < 6; j++) {
            if (casillas[i][j])
                std::cout << casillas[i][j]->obtenerSimbolo() << " ";
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}

void Tablero_al::colocarPieza_al(Pieza* pieza, int x, int y) {
    casillas[x][y] = pieza;
}

//int Tablero_al::moverPieza_al(int xi, int yi, int xf, int yf) {
//    if (casillas[xi][yi] && casillas[xi][yi]->movimientoValido(xi, yi, xf, yf, casillas)) {
//        // Si hay pieza en destino y es un rey, fin del juego
//        if (casillas[xf][yf] != nullptr) {
//            char simbolo = casillas[xf][yf]->obtenerSimbolo();
//            if (simbolo == 'R' || simbolo == 'r') {
//                delete casillas[xf][yf];
//                casillas[xf][yf] = casillas[xi][yi];
//                casillas[xi][yi] = nullptr;
//                return 2; // Rey capturado
//            }
//        }
//
//        // Movimiento normal
//        delete casillas[xf][yf]; // captura si hay algo
//        casillas[xf][yf] = casillas[xi][yi];
//        casillas[xi][yi] = nullptr;
//
//
//        Pieza* pieza = casillas[xf][yf];
//        if (pieza != nullptr) {
//            char simbolo = pieza->obtenerSimbolo();
//
//            // Peón blanco llega a fila 0
//            if (simbolo == 'P' && xf == 0) {
//                delete casillas[xf][yf];
//                casillas[xf][yf] = new Reina(true);
//                std::cout << "¡Peón blanco promocionado a Reina!\n";
//            }
//
//            // Peón negro llega a fila 3
//            else if (simbolo == 'p' && xf == 3) {
//                delete casillas[xf][yf];
//                casillas[xf][yf] = new Reina(false);
//                std::cout << "¡Peón negro promocionado a Reina!\n";
//            }
//        }
//
//        return 1; // Movimiento válido
//    }
//
//    return 0; // Movimiento inválido
//}
//int Tablero::moverPieza(int xi, int yi, int xf, int yf) {
//    if (xi < 0 || xi > 3 || yi < 0 || yi > 3 || xf < 0 || xf > 3 || yf < 0 || yf > 3) {
//        return 0; // Movimiento fuera del tablero
//    }
//
//    if (!this->Tablero[xi][yi]) {  // Corregido: usar this->
//        return 0; // No hay pieza en la casilla de origen
//    }
//
//    if (!this->Tablero[xi][yi]->movimientoValido(xi, yi, xf, yf, this->Tablero)) { // Corregido: usar this->
//        return 0; // Movimiento inválido para la pieza
//    }
//
//    // Si hay una pieza en la casilla de destino y es del oponente, "captúrala" (reemplázala)
//    // No necesitamos eliminarla explícitamente en este caso, simplemente la reemplazamos
//
//    // Mover la pieza desde el origen al destino
//    this->Tablero[xf][yf] = this->Tablero[xi][yi]; // Corregido: usar this->
//    this->Tablero[xi][yi] = nullptr;       // Corregido: usar this->
//
//    return 1; // Movimiento exitoso
//}


// ? ESTA FUNCIÓN DEBE ESTAR FUERA DE moverPieza
void Tablero_al::cargarLosAlamos() {
    // Limpiar tablero
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }

    // Negras (arriba)
    casillas[0][0] = new Torre(false);
    casillas[0][1] = new Caballo(false);
    casillas[0][2] = new Rey(false);
    casillas[0][3] = new Reina(false);
    casillas[0][4] = new Caballo(false);
    casillas[0][5] = new Torre(false);
   
    // FILA 1 (peones blancos)
    for (int j = 0; j < 6; ++j)
        casillas[1][j] = new Peon(false);


    // Blancas (abajo)
    casillas[5][0] = new Torre(true);
    casillas[5][1] = new Caballo(true);
    casillas[5][2] = new Rey(true);
    casillas[5][3] = new Reina(true);
    casillas[5][4] = new Caballo(true);
    casillas[5][5] = new Torre(true);
    
    // FILA 5 (peones negros)
    for (int j = 0; j < 6; ++j)
        casillas[4][j] = new Peon(true);
}
Pieza* Tablero_al::obtenerPieza_al(int x, int y) {
    if (x < 0 || x >= 6 || y < 0 || y >= 6) return nullptr;
    return casillas[x][y];
}

