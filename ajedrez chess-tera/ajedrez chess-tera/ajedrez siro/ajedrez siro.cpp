#include <iostream>
#include "Tablero.h"

int main() {
    Tablero t;
    int opcion;

    // Menú inicial
    std::cout << "=== MINI-AJEDREZ ===\n";
    std::cout << "1. Jugar Los Álamos\n";
    std::cout << "2. Jugar Silverman 4x4\n";
    std::cout << "Seleccione una opción: ";
    std::cin >> opcion;

    if (opcion == 1) {
        t.cargarLosAlamos();
    }
    else if (opcion == 2) {
        t.cargarSilverman();  // Asegúrate de haber implementado esta función
    }
    else {
        std::cout << "Opción inválida. Cerrando el programa.\n";
        return 0;
    }

    t.mostrar();

    bool turnoBlanco = true;  // true = blancas, false = negras
    int xi, yi, xf, yf;

    while (true) {
        std::cout << "\nTurno de " << (turnoBlanco ? "BLANCAS" : "NEGRAS") << std::endl;
        std::cout << "Mover pieza (xi yi xf yf): ";
        std::cin >> xi >> yi >> xf >> yf;

        Pieza* origen = t.obtenerPieza(xi, yi);

        // Verificar que hay pieza y que es del color correcto
        if (origen == nullptr) {
            std::cout << "No hay pieza en esa casilla.\n";
            continue;
        }
        if (origen->esBlanco != turnoBlanco) {
            std::cout << "Esa pieza no te pertenece.\n";
            continue;
        }

        // Mover pieza y evaluar resultado
        int resultado = t.moverPieza(xi, yi, xf, yf);

        if (resultado == 2) {
            std::cout << "¡REY capturado! " << (turnoBlanco ? "BLANCAS" : "NEGRAS") << " ganan.\n";
            t.mostrar();
            break; // Fin del juego
        }
        else if (resultado == 1) {
            std::cout << "Movimiento válido\n";
            turnoBlanco = !turnoBlanco;
        }
        else {
            std::cout << "Movimiento inválido\n";
        }

        t.mostrar();
    }

    return 0;
}
