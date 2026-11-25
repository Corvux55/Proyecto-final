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
    float xRuido;
    float yRuido;

    std::vector<std::pair<float, float>> puntosPatrulla;
    int indicePatrullaActual;
    float tiempoInvestigacion;
    float anguloVision;
public:
    Enemigo(float x = 0.0f, float y = 0.0f);

    void actualizarFisica(float dt) override;

    void percibir(float xJugador, float yJugador, bool hayRuido, float xRuido, float yRuido,bool escondido);
    void razonar();
    void actuar(float dt, float xJugador, float yJugador);
    void aprender();

    Estado obtenerEstado() const;
    std::string obtenerEstadoComoTexto() const;
    void actualizarVision(float xJugador, float yJugador);
};

#endif // ENEMIGO_H