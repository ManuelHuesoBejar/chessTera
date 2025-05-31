#ifndef TABLERO_AL_H
#define TABLERO_AL_H

#include "Pieza.h"

class Tablero_al
{
private:
    Pieza* casillas[6][6];

public:
    Tablero_al();
    ~Tablero_al();

    void colocarPieza_al(Pieza* pieza, int x, int y);
    int moverPieza_al(int xi, int yi, int xf, int yf);
    void cargarLosAlamos();
    void mostrar_al();
    Pieza* obtenerPieza_al(int x, int y);

    bool reyEnJaque(bool esBlanco);
    bool esJaqueMate(bool turnoBlanco);
};

#endif



