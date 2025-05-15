#ifndef TORRE_H
#define TORRE_H

#include "Pieza.h"

class Torre : public Pieza {
public:
    Torre(bool esBlanco);
    char obtenerSimbolo() const override;
    bool movimientoValido(int xi, int yi, int xf, int yf, Pieza*** tablero, int filas, int columnas) override;
    std::string obtenerNombreClave() const override;

};

#endif
