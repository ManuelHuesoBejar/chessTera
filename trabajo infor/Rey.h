#ifndef REY_H
#define REY_H

#include "Pieza.h"

class Rey : public Pieza {
public:
    Rey(bool esBlanco);
    char obtenerSimbolo() const override;
    bool movimientoValido(int xi, int yi, int xf, int yf, Pieza* tablero[6][6], int filas, int columnas) override;
    std::string obtenerNombreClave() const override;

};

#endif
