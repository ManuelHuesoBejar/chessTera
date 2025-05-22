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
/*
int Tablero_al::moverPieza_al(int xi, int yi, int xf, int yf) {
    if (xi < 0 || xi > 5 || yi < 0 || yi > 5 || xf < 0 || xf > 5 || yf < 0 || yf > 5)
        return 0;

    if (!casillas[xi][yi])
        return 0;

    if (!casillas[xi][yi]->movimientoValido(xi, yi, xf, yf, casillas, 6, 6))
        return 0;


    if (casillas[xf][yf] != nullptr) {
        char simbolo = casillas[xf][yf]->obtenerSimbolo();
        if (simbolo == 'R' || simbolo == 'r') {
            delete casillas[xf][yf];
            casillas[xf][yf] = casillas[xi][yi];
            casillas[xi][yi] = nullptr;
            return 2; // Rey capturado
        }
    }

    delete casillas[xf][yf];
    casillas[xf][yf] = casillas[xi][yi];
    casillas[xi][yi] = nullptr;

    Pieza* pieza = casillas[xf][yf];
    if (pieza) {
        char simbolo = pieza->obtenerSimbolo();
        if (simbolo == 'P' && xf == 0) {
            delete pieza;
            casillas[xf][yf] = new Reina(true);
        }
        else if (simbolo == 'p' && xf == 5) {
            delete pieza;
            casillas[xf][yf] = new Reina(false);
        }
    }

    return 1;
}*/

int Tablero_al::moverPieza_al(int xi, int yi, int xf, int yf) {
    if (xi < 0 || xi >= 6 || yi < 0 || yi >= 6 || xf < 0 || xf >= 6 || yf < 0 || yf >= 6)
        return 0;

    Pieza* origen = casillas[xi][yi];
    if (!origen) return 0;

    // Verifica si el movimiento es válido según la pieza
   if (!origen->movimientoValido(xi, yi, xf, yf, (Pieza**)casillas, 6, 6))
        return 0;

    Pieza* destino = casillas[xf][yf];

    // No se puede capturar al rey
    if (destino) {
        char simb = destino->obtenerSimbolo();
        if (simb == 'R' || simb == 'r') {
            std::cout << "No se puede capturar al rey.\n";
            return 0;
        }
    }

    // Simular el movimiento para verificar si deja al propio rey en jaque
    Pieza* tempDestino = destino;
    casillas[xf][yf] = origen;
    casillas[xi][yi] = nullptr;

    // Si el movimiento deja a tu rey en jaque, lo deshacemos
    if (reyEnJaque(origen->esBlanca())) {
        casillas[xi][yi] = origen;
        casillas[xf][yf] = tempDestino;
        std::cout << "¡Estás en jaque! Debes salir del jaque primero.\n";
        return 0;
    }

    // Movimiento válido, eliminar pieza destino si no era nula
    if (tempDestino) {
        delete tempDestino;
    }

    // Promoción de peón
    char simbolo = origen->obtenerSimbolo();
    if (simbolo == 'P' && xf == 0) {
        delete casillas[xf][yf];
        casillas[xf][yf] = new Reina(true);
    }
    else if (simbolo == 'p' && xf == 5) {
        delete casillas[xf][yf];
        casillas[xf][yf] = new Reina(false);
    }

    return 1;
}

void Tablero_al::cargarLosAlamos() {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }

    // Negras
    casillas[0][0] = new Torre(false);
    casillas[0][1] = new Caballo(false);
    casillas[0][2] = new Rey(false);
    casillas[0][3] = new Reina(false);
    casillas[0][4] = new Caballo(false);
    casillas[0][5] = new Torre(false);

    for (int j = 0; j < 6; ++j)
        casillas[1][j] = new Peon(false);

    // Blancas
    casillas[5][0] = new Torre(true);
    casillas[5][1] = new Caballo(true);
    casillas[5][2] = new Rey(true);
    casillas[5][3] = new Reina(true);
    casillas[5][4] = new Caballo(true);
    casillas[5][5] = new Torre(true);

    for (int j = 0; j < 6; ++j)
        casillas[4][j] = new Peon(true);
}

Pieza* Tablero_al::obtenerPieza_al(int x, int y) {
    if (x < 0 || x >= 6 || y < 0 || y >= 6) return nullptr;
    return casillas[x][y];
}
bool Tablero_al::reyEnJaque(bool esBlanco) {
    int reyX = -1, reyY = -1;

    // Buscar el rey del color actual
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            Pieza* p = casillas[i][j];
            if (p && p->esBlanca() == esBlanco && (p->obtenerSimbolo() == 'R' || p->obtenerSimbolo() == 'r')) {
                reyX = i;
                reyY = j;
                break;
            }
        }
    }

    if (reyX == -1 || reyY == -1) return false; // No hay rey en el tablero

    // Verificar si alguna pieza enemiga puede atacar al rey
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            Pieza* atacante = casillas[i][j];
            if (atacante && atacante->esBlanca() != esBlanco) {
                if (atacante->movimientoValido(i, j, reyX, reyY, (Pieza**)casillas, 6, 6)) {
                    return true;
                }
            }
        }
    }

    return false;
}

//#include "Tablero_al.h"
//#include <iostream>
//#include "Rey.h"
//#include "Reina.h"
//#include "Peon.h"
//#include "Torre.h"
//#include "Caballo.h"
//
//Tablero_al::Tablero_al() {
//    for (int i = 0; i < 6; i++)
//        for (int j = 0; j < 6; j++)
//            casillas[i][j] = nullptr;
//}
//
//Tablero_al::~Tablero_al() {
//    for (int i = 0; i < 6; i++)
//        for (int j = 0; j < 6; j++)
//            delete casillas[i][j];
//}
//
//void Tablero_al::mostrar_al() {
//    std::cout << "  0 1 2 3 4 5\n";
//    for (int i = 0; i < 6; i++) {
//        std::cout << i << " ";
//        for (int j = 0; j < 6; j++) {
//            if (casillas[i][j])
//                std::cout << casillas[i][j]->obtenerSimbolo() << " ";
//            else
//                std::cout << ". ";
//        }
//        std::cout << std::endl;
//    }
//}
//
//void Tablero_al::colocarPieza_al(Pieza* pieza, int x, int y) {
//    casillas[x][y] = pieza;
//}
//
//int Tablero_al::moverPieza_al(int xi, int yi, int xf, int yf) {
//    if (xi < 0 || xi > 5 || yi < 0 || yi > 5 || xf < 0 || xf > 5 || yf < 0 || yf > 5)
//        return 0;
//
//    if (!casillas[xi][yi])
//        return 0;
//
//    if (!casillas[xi][yi]->movimientoValido(xi, yi, xf, yf, casillas, 6, 6))
//        return 0;
//
//
//    if (casillas[xf][yf] != nullptr) {
//        char simbolo = casillas[xf][yf]->obtenerSimbolo();
//        if (simbolo == 'R' || simbolo == 'r') {
//            delete casillas[xf][yf];
//            casillas[xf][yf] = casillas[xi][yi];
//            casillas[xi][yi] = nullptr;
//            return 2; // Rey capturado
//        }
//    }
//
//    delete casillas[xf][yf];
//    casillas[xf][yf] = casillas[xi][yi];
//    casillas[xi][yi] = nullptr;
//
//    Pieza* pieza = casillas[xf][yf];
//    if (pieza) {
//        char simbolo = pieza->obtenerSimbolo();
//        if (simbolo == 'P' && xf == 0) {
//            delete pieza;
//            casillas[xf][yf] = new Reina(true);
//        }
//        else if (simbolo == 'p' && xf == 5) {
//            delete pieza;
//            casillas[xf][yf] = new Reina(false);
//        }
//    }
//
//    return 1;
//}
//
//void Tablero_al::cargarLosAlamos() {
//    for (int i = 0; i < 6; i++)
//        for (int j = 0; j < 6; j++) {
//            delete casillas[i][j];
//            casillas[i][j] = nullptr;
//        }
//
//    // Negras
//    casillas[0][0] = new Torre(false);
//    casillas[0][1] = new Caballo(false);
//    casillas[0][3] = new Rey(false);
//    casillas[0][2] = new Reina(false);
//    casillas[0][4] = new Caballo(false);
//    casillas[0][5] = new Torre(false);
//
//    for (int j = 0; j < 6; ++j)
//        casillas[1][j] = new Peon(false);
//
//    // Blancas
//    casillas[5][0] = new Torre(true);
//    casillas[5][1] = new Caballo(true);
//    casillas[5][3] = new Rey(true);
//    casillas[5][2] = new Reina(true);
//    casillas[5][4] = new Caballo(true);
//    casillas[5][5] = new Torre(true);
//
//    for (int j = 0; j < 6; ++j)
//        casillas[4][j] = new Peon(true);
//}
//
//Pieza* Tablero_al::obtenerPieza_al(int x, int y) {
//    if (x < 0 || x >= 6 || y < 0 || y >= 6) return nullptr;
//    return casillas[x][y];
//}
//
//
//
///*#include "Tablero_al.h"
//#include "Peon.h"
//#include "Reina.h"
//#include "Rey.h"
//#include "Torre.h"
//#include "Caballo.h"
//#include <iostream>
//
//Tablero_al::Tablero_al() {
//    for (int i = 0; i < 4; i++)
//        for (int j = 0; j < 4; j++)
//            casillas[i][j] = nullptr;
//}
//
//Tablero_al::~Tablero_al() {
//    for (int i = 0; i < 4; i++)
//        for (int j = 0; j < 4; j++)
//            delete casillas[i][j];
//}
//
//void Tablero_al::colocarPieza_al(Pieza* pieza, int x, int y) {
//    casillas[x][y] = pieza;
//}
//
//int Tablero_al::moverPieza_al(int xi, int yi, int xf, int yf) {
//    if (xi < 0 || xi > 3 || yi < 0 || yi > 3 || xf < 0 || xf > 3 || yf < 0 || yf > 3)
//        return 0;
//
//    if (!casillas[xi][yi])
//        return 0;
//
//    if (!casillas[xi][yi]->movimientoValido(xi, yi, xf, yf, casillas, 4, 4))
//        return 0;
//
//    if (casillas[xf][yf] != nullptr) {
//        char simbolo = casillas[xf][yf]->obtenerSimbolo();
//        if (simbolo == 'R' || simbolo == 'r') {
//            delete casillas[xf][yf];
//            casillas[xf][yf] = casillas[xi][yi];
//            casillas[xi][yi] = nullptr;
//            return 2;
//        }
//    }
//
//    delete casillas[xf][yf];
//    casillas[xf][yf] = casillas[xi][yi];
//    casillas[xi][yi] = nullptr;
//
//    Pieza* pieza = casillas[xf][yf];
//    if (pieza) {
//        char simbolo = pieza->obtenerSimbolo();
//        if (simbolo == 'P' && xf == 0) {
//            delete pieza;
//            casillas[xf][yf] = new Reina(true);
//        }
//        else if (simbolo == 'p' && xf == 3) {
//            delete pieza;
//            casillas[xf][yf] = new Reina(false);
//        }
//    }
//
//    return 1;
//}
//
//Pieza* Tablero_al::obtenerPieza_al(int x, int y) {
//    if (x < 0 || x >= 4 || y < 0 || y >= 4)
//        return nullptr;
//    return casillas[x][y];
//}
//
//void Tablero_al::cargarSilverman() {
//    // Limpiar tablero
//    for (int i = 0; i < 4; ++i)
//        for (int j = 0; j < 4; ++j) {
//            delete casillas[i][j];
//            casillas[i][j] = nullptr;
//        }
//
//    // Negras arriba
//    casillas[0][0] = new Torre(false);
//    casillas[0][1] = new Rey(false);
//    casillas[0][2] = new Reina(false);
//    casillas[0][3] = new Torre(false);
//
//    for (int j = 0; j < 4; ++j)
//        casillas[1][j] = new Peon(false);
//
//    // Blancas abajo
//    for (int j = 0; j < 4; ++j)
//        casillas[2][j] = new Peon(true);
//
//    casillas[3][0] = new Torre(true);
//    casillas[3][1] = new Rey(true);
//    casillas[3][2] = new Reina(true);
//    casillas[3][3] = new Torre(true);
//}*/
