#include "Tablero.h"
#include <iostream>
#include "Rey.h"
#include "Reina.h"
#include "Peon.h"
#include "Torre.h"
#include "Caballo.h"
#include "Tablero_al.h"

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

bool Tablero::reyEnJaque(bool esBlanco) {
    int reyX = -1, reyY = -1;

    // Buscar la posición del rey del color actual
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Pieza* p = casillas[i][j];
            if (p && p->esBlanca() == esBlanco && (p->obtenerSimbolo() == 'R' || p->obtenerSimbolo() == 'r')) {
                reyX = i;
                reyY = j;
                break;
            }
        }
    }

    if (reyX == -1 || reyY == -1) return false; // Rey no encontrado

    // Buscar si alguna pieza enemiga puede capturarlo
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Pieza* atacante = casillas[i][j];
            if (atacante && atacante->esBlanca() != esBlanco) {
                if (atacante->movimientoValido(i, j, reyX, reyY, (Pieza**)casillas, 4, 4)) {
                    return true;
                }
            }
        }
    }

    return false;
}

int Tablero::moverPieza(int xi, int yi, int xf, int yf) {
    if (xi < 0 || xi >= 4 || yi < 0 || yi >= 4 || xf < 0 || xf >= 4 || yf < 0 || yf >= 4)
        return 0;

    Pieza* origen = casillas[xi][yi];
    Pieza* destino = casillas[xf][yf];

    if (!origen) return 0;

    if (!origen->movimientoValido(xi, yi, xf, yf, (Pieza**)casillas, 4, 4))
        return 0;

    // Simular movimiento
    casillas[xf][yf] = origen;
    casillas[xi][yi] = nullptr;

    bool jaque = reyEnJaque(origen->esBlanca());

    // Revertir si hay jaque
    casillas[xi][yi] = origen;
    casillas[xf][yf] = destino;

    if (jaque) {
        std::cout << "¡Movimiento inválido: deja al rey en jaque!\n";
        return 0;
    }

    // Captura de rey
    if (destino != nullptr) {
        char simbolo = destino->obtenerSimbolo();
        if (simbolo == 'R' || simbolo == 'r') {
            delete destino;
            casillas[xf][yf] = origen;
            casillas[xi][yi] = nullptr;
            return 2; // Fin del juego
        }
        delete destino;
    }

    // Movimiento final
    casillas[xf][yf] = origen;
    casillas[xi][yi] = nullptr;

    // Promoción de peón
    char simbolo = origen->obtenerSimbolo();
    if (simbolo == 'P' && xf == 0) {
        delete casillas[xf][yf];
        casillas[xf][yf] = new Reina(true);
    }
    else if (simbolo == 'p' && xf == 3) {
        delete casillas[xf][yf];
        casillas[xf][yf] = new Reina(false);
    }

    return 1;
}

void Tablero::cargarSilverman() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j) {
            delete casillas[i][j];
            casillas[i][j] = nullptr;
        }

    casillas[0][0] = new Torre(false);
    casillas[0][1] = new Reina(false);
    casillas[0][2] = new Rey(false);
    casillas[0][3] = new Torre(false);

    for (int j = 0; j < 4; ++j)
        casillas[1][j] = new Peon(false);

    for (int j = 0; j < 4; ++j)
        casillas[2][j] = new Peon(true);

    casillas[3][0] = new Torre(true);
    casillas[3][1] = new Reina(true);
    casillas[3][2] = new Rey(true);
    casillas[3][3] = new Torre(true);
}
bool Tablero::esJaqueMate(bool turnoBlanco) {
    // Paso 1: ¿está el rey en jaque?
    if (!reyEnJaque(turnoBlanco)) return false;

    // Paso 2: buscar si alguna pieza del jugador puede salvarse
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            Pieza* p = casillas[i][j];
            if (p && p->esBlanca() == turnoBlanco) {
                // Probar todos los destinos posibles
                for (int x = 0; x < 4; ++x) {
                    for (int y = 0; y < 4; ++y) {
                        if (p->movimientoValido(i, j, x, y, (Pieza**)casillas, 4, 4)) {
                            // Simular movimiento
                            Pieza* temp = casillas[x][y];
                            casillas[x][y] = p;
                            casillas[i][j] = nullptr;

                            bool sigueEnJaque = reyEnJaque(turnoBlanco);

                            // Deshacer
                            casillas[i][j] = p;
                            casillas[x][y] = temp;

                            if (!sigueEnJaque) {
                                return false; // hay al menos un movimiento que evita el jaque
                            }
                        }
                    }
                }
            }
        }
    }

    // Si ninguna pieza puede salvarse del jaque:
    return true;
}
