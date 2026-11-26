#ifndef OBJETO_H
#define OBJETO_H

#include "entidad.h"

class Objeto: public Entidad{
public:
    enum TipoObjeto{PIEDRA,CAJA,CHARCO,CADENA};

private:
    TipoObjeto tipo;
    float peso;
    bool activo; // Para saber si la piedra sigue volando o no

    float ancho;
    float alto;
    float anguloOscilacion;
    float velocidadAngular;
    bool estaOscilando;
    bool esTopDown;
    float xInicial;
    float yInicial;
    float distanciaMaxima;
public:
    Objeto(float x = 0.0f, float y = 0.0f, TipoObjeto t = PIEDRA, float ancho = 40.0f, float alto = 40.0f);
    void actualizarFisica(float dt) override;
    TipoObjeto obtenerTipo() const;
    bool estaActivo() const;
    float obtenerPeso() const;
    float obtenerAncho() const;
    float obtenerAlto() const;
    float obtenerAnguloOscilacion() const;
    void iniciarOscilacion();
    void darImpulso(float direccion);
    float obtenerVelocidadAngular() const;
    void establecerActivo(bool a);
    void establecerTopDown(bool td);
    void establecerDistanciaMaxima(float distancia);
};
#endif // OBJETO_H