#include "jugador.h"

Jugador::Jugador(float x, float y):Entidad(x, y), estaAgachado(false), piedrasInventario(3), enElSuelo(false),enLodo(false),colgadoDeCadena(false),tiempoGraciaCadena(0.0f){
}

void Jugador::actualizarFisica(float dt){
    velocidadY += 980.0f * dt; // gravedad ->980 px/s²
    posicionX += velocidadX * dt;
    posicionY += velocidadY * dt;
    if (tiempoGraciaCadena > 0.0f) {
        tiempoGraciaCadena -= dt;
    }

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
    if (enLodo) {
        velocidadX *= 0.5f; // Se detiene mucho más rápido
    } else {
        velocidadX *= 0.85f; // Fricción normal
    }
}

void Jugador::moverse(float direccion){
    float multiplicador = 1.0f;
    if (enLodo){
        multiplicador = 0.3f; // El lodo reduce la velocidad al 30%
    }
    if (estaAgachado) {
        velocidadX = (direccion * 100.0f)*multiplicador; // lento agachado
    } else {
        velocidadX = (direccion * 300.0f)*multiplicador; // rapido de pie
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
void Jugador::establecerEnLodo(bool lodo) {enLodo = lodo;}
bool Jugador::obtenerEnLodo() const {return enLodo;}
void Jugador::establecerColgado(bool colgado){colgadoDeCadena= colgado;}
bool Jugador::obtenerColgado() const {return colgadoDeCadena;}
void Jugador::establecerTiempoGracia(float tiempo) {tiempoGraciaCadena = tiempo;}
float Jugador::obtenerTiempoGracia() const {return tiempoGraciaCadena;}