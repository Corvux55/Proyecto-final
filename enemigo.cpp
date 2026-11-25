#include "enemigo.h"
#include <cmath>
#include <iostream>
Enemigo::Enemigo(float x, float y):Entidad(x, y), estadoActual(PATRULLANDO), rangoVision(200.0f), radioEscucha(500.0f), contadorEngaños(0), indicePatrullaActual(0),tiempoInvestigacion(0.0f){
    // por donde va a vigilar
    puntosPatrulla.push_back({300.0f, 600.0f});
    puntosPatrulla.push_back({1000.0f, 600.0f});
}
void Enemigo::actualizarFisica(float dt){
    if (tiempoInvestigacion > 0.0f){
        tiempoInvestigacion -= dt;
    }
    posicionX += velocidadX * dt;
    posicionY += velocidadY * dt;
}

void Enemigo::percibir(float xJugador, float yJugador, bool hayRuido, float xRuido, float yRuido,bool escondido){
    float dx = xJugador - posicionX;
    float dy = yJugador - posicionY;
    float distanciaJugador = std::sqrt(dx*dx + dy*dy);

    if (!escondido && distanciaJugador < rangoVision){
        estadoActual = PERSIGUIENDO;
        return;
    }
    //si escucha investiga, sino no pasa nada
    if (hayRuido) {
        float dxR = xRuido - posicionX;
        float dyR = yRuido - posicionY;
        float distanciaRuido = std::sqrt(dxR*dxR + dyR*dyR);

        if (distanciaRuido < radioEscucha){
            estadoActual = INVESTIGANDO;
            this->xRuido = xRuido;
            this->yRuido = yRuido;
            tiempoInvestigacion = 2.0f;
            return;
        }
    }
    if (estadoActual == INVESTIGANDO && tiempoInvestigacion > 0.0f) {
        return; // Se queda investigando
    }
    estadoActual = PATRULLANDO;
}

void Enemigo::razonar(){
    // En este diseño, la decisión se toma directamente en percibir()
//a la final no se uso, es codigo muerto, si despues veo que agregarle lo hago, sino se borra
}

void Enemigo::actuar(float dt, float xJugador, float yJugador){
    switch (estadoActual){
    case PATRULLANDO: {
        if (indicePatrullaActual < (int)puntosPatrulla.size()){
            float objetivoX = puntosPatrulla[indicePatrullaActual].first;
            float objetivoY = puntosPatrulla[indicePatrullaActual].second;

            if (std::abs(posicionX - objetivoX) < 5.0f){
                posicionX = objetivoX;
                velocidadX = 0.0f;
            } else {
                if (objetivoX > posicionX) velocidadX = 100.0f;
                else velocidadX = -100.0f;
            }

            if (std::abs(posicionY - objetivoY) < 5.0f){
                posicionY = objetivoY;
                velocidadY = 0.0f;
            } else {
                if (objetivoY > posicionY) velocidadY = 100.0f;
                else velocidadY = -100.0f;
            }

            // si llego al punto pasa al siguiente
            if (std::abs(posicionX - objetivoX) < 5.0f && std::abs(posicionY - objetivoY) < 5.0f){
                indicePatrullaActual = (indicePatrullaActual + 1) % puntosPatrulla.size();
            }
        }
        break;
    }
    case INVESTIGANDO: {
        // moverse a los puntos de ruido
        if (this->xRuido > posicionX + 10.0f) velocidadX = 150.0f;
        else if (this->xRuido < posicionX - 10.0f) velocidadX = -150.0f;
        else velocidadX = 0.0f;

        if (this->yRuido > posicionY + 10.0f) velocidadY = 150.0f;
        else if (this->yRuido < posicionY - 10.0f) velocidadY = -150.0f;
        else velocidadY = 0.0f;
        break;
    }
    case PERSIGUIENDO: {
        //ya persigue en todas direcciones
        if (xJugador > posicionX + 5.0f) velocidadX = 250.0f;
        else if (xJugador < posicionX - 5.0f) velocidadX = -250.0f;
        else velocidadX = 0.0f;

        if (yJugador > posicionY + 5.0f) velocidadY = 250.0f;
        else if (yJugador < posicionY - 5.0f) velocidadY = -250.0f;
        else velocidadY = 0.0f;
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
void Enemigo::actualizarVision(float xJugador, float yJugador) {
    // calcular angulo a jugadr
    float dx = xJugador - posicionX;
    float dy = yJugador - posicionY;
    float distancia = std::sqrt(dx*dx + dy*dy);

    if (distancia < rangoVision){
        estadoActual = PERSIGUIENDO;
    }
}