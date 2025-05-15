#ifndef PIEZA_H
#define PIEZA_H

#include <string>  

class Pieza {
protected:
    bool esBlanco;

public:
    virtual char obtenerSimbolo() const = 0;
    virtual std::string obtenerNombreClave() const = 0;
    virtual bool movimientoValido(int xi, int yi, int xf, int yf, Pieza*** tablero,int filas,int columnas) = 0;

    virtual bool esBlanca() const { return esBlanco; } 
    virtual ~Pieza() {}
};


#endif
