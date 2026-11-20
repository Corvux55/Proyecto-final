#ifndef OBJETO_H
#define OBJETO_H

#include "entidad.h"

class Objeto: public Entidad{
public:
    enum TipoObjeto{PIEDRA,CAJA};

private:
    TipoObjeto tipo;
    float peso;
    bool activo; // Para saber si la piedra sigue volando o no

public:
    Objeto(float x = 0.0f, float y = 0.0f, TipoObjeto t = PIEDRA);
    void actualizarFisica(float dt) override;

    TipoObjeto obtenerTipo() const;
    bool estaActivo() const;
    float obtenerPeso() const;
};

#endif // OBJETO_H