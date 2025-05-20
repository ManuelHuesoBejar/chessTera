
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



/*#include "Tablero_al.h"
#include "Peon.h"
#include "Reina.h"
#include "Rey.h"
#include "Torre.h"
#include "Caballo.h"
#include <iostream>

Tablero_al::Tablero_al() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            casillas[i][j] = nullptr;
}

Tablero_al::~Tablero_al() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            delete casillas[i][j];
}

void Tablero_al::colocarPieza_al(Pieza* pieza, int x, int y) {
    casillas[x][y] = pieza;
}

int Tablero_al::moverPieza_al(int xi, int yi, int xf, int yf) {
    if (xi < 0 || xi > 3 || yi < 0 || yi > 3 || xf < 0 || xf > 3 || yf < 0 || yf > 3)
        return 0;

    if (!casillas[xi][yi])
        return 0;

    if (!casillas[xi][yi]->movimientoValido(xi, yi, xf, yf, casillas, 4, 4))
        return 0;

    if (casillas[xf][yf] != nullptr) {
        char simbolo = casillas[xf][yf]->obtenerSimbolo();
        if (simbolo == 'R' || simbolo == 'r') {
            delete casillas[xf][yf];
            casillas[xf][yf] = casillas[xi][yi];
            casillas[xi][yi] = nullptr;
            return 2;
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
        else if (simbolo == 'p' && xf == 3) {
            delete pieza;
            casillas[xf][yf] = new Reina(false);
        }
    }

    return 1;
}

Pieza* Tablero_al::obtenerPieza_al(int x, int y) {
    if (x < 0 || x >= 4 || y < 0 || y >= 4)
        return nullptr;
    return casillas[x][y];
}

void Tablero_al::cargarLosAlamos() {
    // Limpiar tablero
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }

    // Negras arriba
    casillas[0][0] = new Torre(false);
    casillas[0][1] = new Rey(false);
    casillas[0][2] = new Reina(false);
    casillas[0][3] = new Torre(false);

    for (int j = 0; j < 4; ++j)
        casillas[1][j] = new Peon(false);

    // Blancas abajo
    for (int j = 0; j < 4; ++j)
        casillas[2][j] = new Peon(true);

    casillas[3][0] = new Torre(true);
    casillas[3][1] = new Rey(true);
    casillas[3][2] = new Reina(true);
    casillas[3][3] = new Torre(true);
}*/
