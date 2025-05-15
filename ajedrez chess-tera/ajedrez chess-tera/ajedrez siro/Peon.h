#ifndef PEON_H
#define PEON_H

#include "Pieza.h"

class Peon : public Pieza {
public:
    Peon(bool esBlanco);
    char obtenerSimbolo() const override;
    bool movimientoValido(int xi, int yi, int xf, int yf, Pieza*** tablero, int filas, int columnas) override;
    std::string obtenerNombreClave() const override;

};

#endif
