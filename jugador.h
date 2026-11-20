#ifndef JUGADOR_H
#define JUGADOR_H

#include "entidad.h"

class Jugador : public Entidad{
private:
    bool estaAgachado;
    int piedrasInventario;
    bool enElSuelo;

public:
    Jugador(float x = 0.0f, float y = 0.0f);

    // Sobrescribimos el método de la clase base
    void actualizarFisica(float dt) override;

    void moverse(float direccion); // -1 izquierda, +1 derecha, 0 quieto
    void saltar();
    void agacharse(bool agachado);
    void lanzarPiedra();

    bool obtenerAgachado() const;
    int obtenerPiedras() const;
    bool obtenerEnSuelo() const;
};

#endif // JUGADOR_H