#include "jugador.h"

Jugador::Jugador(float x, float y):Entidad(x, y), estaAgachado(false), piedrasInventario(3), enElSuelo(false){
}

void Jugador::actualizarFisica(float dt){
    velocidadY += 980.0f * dt; // gravedad ->980 px/s²
    posicionX += velocidadX * dt;
    posicionY += velocidadY * dt;

    // Colision con el suelo por ahora un suelo fijo en Y=600->se cambiara despues de pruebas si es necesario
    if(posicionY >= 600.0f){
        posicionY = 600.0f;
        velocidadY = 0.0f;
        enElSuelo = true;
    }
    else{
        enElSuelo = false;
    }

    // fricción horizontal
    velocidadX *= 0.85f;
}

void Jugador::moverse(float direccion){
    if (estaAgachado) {
        velocidadX = direccion * 100.0f; // lento agachado
    } else {
        velocidadX = direccion * 300.0f; // rapido de pie
    }
}

void Jugador::saltar(){
    if (enElSuelo && !estaAgachado){
        velocidadY = -500.0f; // Impulso hacia arriba
        enElSuelo = false;
    }
}

void Jugador::agacharse(bool agachado){
    estaAgachado = agachado;
}

void Jugador::lanzarPiedra(){
    if (piedrasInventario > 0){
        piedrasInventario--;
    }
}

bool Jugador::obtenerAgachado() const {return estaAgachado;}
int Jugador::obtenerPiedras() const {return piedrasInventario;}
bool Jugador::obtenerEnSuelo() const {return enElSuelo;}