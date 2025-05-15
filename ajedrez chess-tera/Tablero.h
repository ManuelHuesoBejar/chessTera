#ifndef TABLERO_H
#define TABLERO_H

#include "Pieza.h"

class Tablero {
private:
    Pieza* casillas[4][4];
    //Pieza*** casillas;
    //int filas, columnas;
public:
    Tablero();
    ~Tablero();
    void mostrar();
    void colocarPieza(Pieza* pieza, int x, int y);
    int moverPieza(int xi, int yi, int xf, int yf); // 0 = inv�lido, 1 = v�lido, 2 = rey capturado
    void cargarLosAlamos();
    Pieza* obtenerPieza(int x, int y);
    void cargarSilverman();

    /*int obtenerFilas() const { return filas; }
    int obtenerColumnas() const { return columnas; }*/

};

#endif
