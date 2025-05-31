#ifndef TABLERO_H
#define TABLERO_H

#include "Pieza.h"

class Tablero {
private:
    Pieza* casillas[4][4];

public:
    Tablero();
    ~Tablero();
    void mostrar();
    void colocarPieza(Pieza* pieza, int x, int y);
    int moverPieza(int xi, int yi, int xf, int yf); // 0 = inválido, 1 = válido, 2 = rey capturado

    Pieza* obtenerPieza(int x, int y);
    void cargarSilverman();
    bool reyEnJaque(bool esBlanco);
    bool esJaqueMate(bool turnoBlanco);
    };



#endif
