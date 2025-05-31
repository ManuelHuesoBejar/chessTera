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
    const int FILAS = 6;
    const int COLUMNAS = 6;
    int reyX = -1, reyY = -1;

    // 1) Localizar al rey y salir de ambos bucles al encontrarlo
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            Pieza* p = casillas[i][j];
            if (p && p->esBlanca() == esBlanco) {
                char s = p->obtenerSimbolo();
                if (s == 'R' || s == 'r') {
                    reyX = i;
                    reyY = j;
                    break;
                }
            }
        }
        if (reyX != -1) break;
    }

    if (reyX < 0) {
        std::cout << "[Debug reyEnJaque] No se encontro el rey." << std::endl;
        return false;
    }
    std::cout << "[Debug reyEnJaque] Rey en (" << reyX << "," << reyY << ")" << std::endl;

    // 2) Comprobar si alguna pieza enemiga puede moverse al rey
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            Pieza* atacante = casillas[i][j];
            if (atacante && atacante->esBlanca() != esBlanco) {
                if (atacante->movimientoValido(
                    i, j,
                    reyX, reyY,
                    (Pieza**)casillas,
                    FILAS, COLUMNAS)) {
                    std::cout << "[Debug reyEnJaque] Ataque detectado por pieza en ("
                        << i << "," << j << ")" << std::endl;
                    return true;
                }
            }
        }
    }

    // 3) Ningun ataque valido -> no esta en jaque
    return false;
}

bool Tablero_al::esJaqueMate(bool turnoBlanco) {
    const int FILAS = 6;
    const int COLUMNAS = 6;

    // 1) Si no hay jaque, no puede ser jaque mate
    if (!reyEnJaque(turnoBlanco)) {
        std::cout << "[Debug] No esta en jaque, no hay jaque mate." << std::endl;
        return false;
    }

    // 2) Simular cada movimiento propio para ver si alguno quita el jaque
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            Pieza* p = casillas[i][j];
            if (!p || p->esBlanca() != turnoBlanco)
                continue;

            for (int x = 0; x < FILAS; ++x) {
                for (int y = 0; y < COLUMNAS; ++y) {
                    if (x == i && y == j)
                        continue;
                    if (p->movimientoValido(i, j, x, y,
                        (Pieza**)casillas,
                        FILAS, COLUMNAS)) {
                        // simular
                        Pieza* backup = casillas[x][y];
                        casillas[x][y] = p;
                        casillas[i][j] = nullptr;

                        bool sigueEnJaque = reyEnJaque(turnoBlanco);

                        // deshacer
                        casillas[i][j] = p;
                        casillas[x][y] = backup;

                        if (!sigueEnJaque) {
                            std::cout << "[Debug] Movimiento de (" << i << "," << j;
                            //           << ") a (" << x << "," << y << ") quita el jaque."
                            //           << std::endl;
                            return false;
                        }
                    }
                }
            }
        }
    }

    // ningun movimiento evita el jaque -> jaque mate
    std::cout << "[Debug] Jaque mate detectado." << std::endl;
    return true;
}

