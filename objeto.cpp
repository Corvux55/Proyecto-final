#include "objeto.h"
#include <cmath>

Objeto::Objeto(float x, float y, TipoObjeto t, float ancho, float alto)
    :Entidad(x, y), tipo(t), peso(1.0f), activo(false), ancho(ancho), alto(alto), anguloOscilacion(0.0f),velocidadAngular(0.0f), estaOscilando(false),esTopDown(false){
}
void Objeto::iniciarOscilacion() {
    estaOscilando = true;
    velocidadAngular = 1.0f; // Un pequeño empujon pa iniciar movimiento
}
void Objeto::darImpulso(float direccion){
    velocidadAngular += direccion * 5.0f;
}
float Objeto::obtenerVelocidadAngular() const{
    return velocidadAngular;
}
void Objeto::actualizarFisica(float dt){
    // sies una cadena aplicamos Movimiento Oscilatorio
    if (tipo == CADENA && estaOscilando){
        float rad = anguloOscilacion * M_PI / 180.0f;//convertir a radianes
        float gravedadPendulo = -1.0f * std::sin(rad); //ajustamos la velocidad para que no sea tan rapida
        velocidadAngular += gravedadPendulo * dt;
        velocidadAngular *= 0.99f; // friccion para qie se detenga si no esta remy
        anguloOscilacion += velocidadAngular * dt;
        if (anguloOscilacion > 60.0f){
            anguloOscilacion = 60.0f;
            velocidadAngular = -velocidadAngular * 0.5f; // Rebote
        } else if (anguloOscilacion < -60.0f) {
            anguloOscilacion = -60.0f;
            velocidadAngular = -velocidadAngular * 0.5f;
        }//ponemos tope para corregir la vueltas en circulos. si se pasa de 60 grados lo devolvemos y le quitamos fuerza

    }
    else if (tipo == PIEDRA && activo){
        //fisicas
        if (!esTopDown){
            velocidadY += 980.0f * dt;
        }
        posicionX += velocidadX * dt;
        posicionY += velocidadY * dt;

        // se detiene si toca suelo
        if (!esTopDown && posicionY >= 600.0f) {
            posicionY = 600.0f;
            activo = false;
        }
        if (esTopDown && (posicionX < 0 || posicionX > 1280 || posicionY < 0 || posicionY > 720)) {
            activo = false;
        }

    }
}

Objeto::TipoObjeto Objeto::obtenerTipo() const {return tipo;}
bool Objeto::estaActivo() const {return activo;}
float Objeto::obtenerPeso() const {return peso;}
float Objeto::obtenerAncho() const {return ancho;}
float Objeto::obtenerAlto() const {return alto;}
float Objeto::obtenerAnguloOscilacion() const {return anguloOscilacion;}
void Objeto::establecerActivo(bool a){
    activo =a;
}
void Objeto::establecerTopDown(bool td){
    esTopDown = td;
}