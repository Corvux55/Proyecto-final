#include "enemigo.h"
#include <cmath>
#include <iostream>

Enemigo::Enemigo(float x, float y):Entidad(x, y), estadoActual(PATRULLANDO), rangoVision(200.0f), radioEscucha(150.0f), contadorEngaños(0), indicePatrullaActual(0){
    // por donde va a vigilar
    puntosPatrulla.push_back({300.0f, 600.0f});
    puntosPatrulla.push_back({1000.0f, 600.0f});
}
void Enemigo::actualizarFisica(float dt){
    posicionX += velocidadX * dt;
    posicionY += velocidadY * dt;
}

void Enemigo::percibir(float xJugador, float yJugador, bool hayRuido, float xRuido, float yRuido){
    float dx = xJugador - posicionX;
    float dy = yJugador - posicionY;
    float distanciaJugador = std::sqrt(dx*dx + dy*dy);

    if (distanciaJugador < rangoVision){
        estadoActual = PERSIGUIENDO;
        return;
    }
    //si escucha investiga, sino no pasa nada
    if (hayRuido) {
        float dxR = xRuido - posicionX;
        float dyR = yRuido - posicionY;
        float distanciaRuido = std::sqrt(dxR*dxR + dyR*dyR);
        if (distanciaRuido < radioEscucha) {
            estadoActual = INVESTIGANDO;
            return;
        }
    }
    estadoActual = PATRULLANDO;
}

void Enemigo::razonar(){
    // En este diseño, la decisión se toma directamente en percibir()
    // Aquí se podría añadir lógica más compleja para el futuro.
}

void Enemigo::actuar(float dt, float xJugador, float yJugador){
    switch (estadoActual){
    case PATRULLANDO: {
        if (indicePatrullaActual < (int)puntosPatrulla.size()) {
            float objetivoX = puntosPatrulla[indicePatrullaActual].first;

            if (std::abs(posicionX - objetivoX) < 5.0f) {
                posicionX = objetivoX;
                velocidadX = 0.0f;
                indicePatrullaActual = (indicePatrullaActual + 1) % puntosPatrulla.size();
            }
            else {
                if (objetivoX > posicionX) {
                    velocidadX = 100.0f;
                } else {
                    velocidadX = -100.0f;
                }
            }
        }
        break;
    }
    case INVESTIGANDO: {
        velocidadX = 150.0f;
        break;
    }
    case PERSIGUIENDO: {
        // calcula la dirección hacia Remy
        if (xJugador > posicionX + 5.0f) {// el 5 es el margen de tolerancia o deadzone
            velocidadX = 250.0f;
        } else if (xJugador < posicionX - 5.0f) {
            velocidadX = -250.0f;
        } else {
            velocidadX = 0.0f; // Ya lo alcanzo
        }
        break;
    }
    }
    actualizarFisica(dt);
}

void Enemigo::aprender(){
    contadorEngaños++;
    // Si el jugador lo engaña 3 veces, el insecto se vuelve mas difícil de distraer
    if (contadorEngaños >= 3){
        radioEscucha *= 0.7f;
    }
}

Enemigo::Estado Enemigo::obtenerEstado() const {
    return estadoActual;
}

std::string Enemigo::obtenerEstadoComoTexto() const {
    switch (estadoActual) {
    case PATRULLANDO: return "PATRULLANDO";
    case INVESTIGANDO: return "INVESTIGANDO";
    case PERSIGUIENDO: return "PERSIGUIENDO";
    default: return "DESCONOCIDO";
    }
}