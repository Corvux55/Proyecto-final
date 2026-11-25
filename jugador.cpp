#include "jugador.h"

Jugador::Jugador(float x, float y):Entidad(x, y), estaAgachado(false), piedrasInventario(3), enElSuelo(false),enLodo(false),colgadoDeCadena(false),tiempoGraciaCadena(0.0f),alturaSuelo(600.0f)
,direccionActual(1.0f){
}

void Jugador::actualizarFisica(float dt){
    velocidadY += 980.0f * dt; // gravedad ->980 px/s²
    posicionX += velocidadX * dt;
    posicionY += velocidadY * dt;
    if (tiempoGraciaCadena > 0.0f) {
        tiempoGraciaCadena -= dt;
    }

    // ya actualiza si se sube a una caja
    if(posicionY >= alturaSuelo){
        posicionY = alturaSuelo;
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
    for (Objeto* piedra : piedrasLanzadas) {
        piedra->actualizarFisica(dt);
    }
}

void Jugador::moverse(float direccion){
    if (direccion != 0.0f){
        direccionActual = direccion; //guarda la ultima direccion
    }
    float multiplicador = 1.0f;
    if (enLodo) {
        multiplicador = 0.3f;
    }
    if (estaAgachado) {
        velocidadX = (direccion * 100.0f) * multiplicador;
    } else {
        velocidadX = (direccion * 300.0f) * multiplicador;
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

Objeto* Jugador::lanzarPiedra(){
    if (piedrasInventario > 0){
        piedrasInventario--;
        //piedra un poco mas arriba que el jgador
        Objeto* nuevaPiedra = new Objeto(posicionX, posicionY - 20.0f, Objeto::PIEDRA, 10.0f, 10.0f);

        nuevaPiedra->establecerVelocidadX(direccionActual * 400.0f);
        nuevaPiedra->establecerVelocidadY(-300.0f);
        nuevaPiedra->establecerActivo(true);

        piedrasLanzadas.push_back(nuevaPiedra);
        return nuevaPiedra;
    }
    return nullptr;
}
Objeto* Jugador::lanzarPiedraRecta(float dirX, float dirY){
    if (piedrasInventario > 0){
        piedrasInventario--;
        Objeto* nuevaPiedra = new Objeto(posicionX, posicionY, Objeto::PIEDRA, 10.0f, 10.0f);
        nuevaPiedra->establecerTopDown(true);
        nuevaPiedra->establecerVelocidadX(dirX * 300.0f);
        nuevaPiedra->establecerVelocidadY(dirY * 300.0f);
        nuevaPiedra->establecerActivo(true);
        piedrasLanzadas.push_back(nuevaPiedra);
        return nuevaPiedra;
    }
    return nullptr;
}
std::vector<Objeto*>& Jugador::obtenerPiedrasLanzadas(){
    return piedrasLanzadas;
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
void Jugador::establecerAlturaSuelo(float altura){alturaSuelo = altura;}
float Jugador::obtenerAlturaSuelo() const {return alturaSuelo;}
//nivel 2
void Jugador::actualizarFisicaTopDown(float dt){
    if (enLodo) {
        velocidadX *= 0.90f * 0.5f; // Se frena mas rapido en lodo
        velocidadY *= 0.90f * 0.5f;
    } else {
        velocidadX *= 0.90f;
        velocidadY *= 0.90f;
    }

    posicionX += velocidadX * dt;
    posicionY += velocidadY * dt;
}

void Jugador::moverseVertical(float direccion){
    velocidadY = direccion * 250.0f;
}