#ifndef CABALLO_H
#define CABALLO_H

#include "Pieza.h"
#include <string>

class Caballo : public Pieza {
public:
    Caballo(bool esBlanco); 

    char obtenerSimbolo() const override;
    bool movimientoValido(int xi, int yi, int xf, int yf, Pieza** tablero, int filas, int columnas) override;
    std::string obtenerNombreClave() const override;

};

#endif
