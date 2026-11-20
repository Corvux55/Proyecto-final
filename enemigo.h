#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "entidad.h"
#include <string>
#include <vector>
#include <utility> // Para usar std::pair

class Enemigo: public Entidad{
public:
    enum Estado{PATRULLANDO,INVESTIGANDO,PERSIGUIENDO};

private:
    Estado estadoActual;
    float rangoVision;
    float radioEscucha;
    int contadorEngaños;

    std::vector<std::pair<float, float>> puntosPatrulla;
    int indicePatrullaActual;

public:
    Enemigo(float x = 0.0f, float y = 0.0f);

    void actualizarFisica(float dt) override;

    void percibir(float xJugador, float yJugador, bool hayRuido, float xRuido, float yRuido);
    void razonar();
    void actuar(float dt);
    void aprender();

    Estado obtenerEstado() const;
    std::string obtenerEstadoComoTexto() const;
};

#endif // ENEMIGO_H