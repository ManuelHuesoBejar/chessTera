#pragma once
#include"Pieza.h"
class Tablero_al
{
private:
    Pieza* casillas[6][6];
    //Pieza*** casillas;
    //int filas, columnas;
public:
    Tablero_al();
    ~Tablero_al();
    void mostrar_al();
    void colocarPieza_al(Pieza* pieza, int x, int y);
    int moverPieza_al(int xi, int yi, int xf, int yf); // 0 = inv�lido, 1 = v�lido, 2 = rey capturado
    void cargarLosAlamos();
    Pieza* obtenerPieza_al(int x, int y);
   // void cargarSilverman();

    /*int obtenerFilas() const { return filas; }
   // int obtenerColumnas() const { return columnas; }*/

};


