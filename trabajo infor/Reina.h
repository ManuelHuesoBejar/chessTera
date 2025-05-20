#ifndef REINA_H
#define REINA_H

#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(bool esBlanco);
    char obtenerSimbolo() const override;
    bool movimientoValido(int xi, int yi, int xf, int yf, Pieza* tablero[6][6], int filas, int columnas) override;
    std::string obtenerNombreClave() const override; 
};


#endif
