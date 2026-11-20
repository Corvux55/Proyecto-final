#ifndef ENTIDAD_H
#define ENTIDAD_H

class Entidad {
protected:
    //lo que se hereda
    float posicionX;
    float posicionY;
    float velocidadX;
    float velocidadY;

public:
    Entidad(float x = 0.0f, float y = 0.0f);
    virtual ~Entidad();

    // metodo virtual puro para obliga a las clases hijas a implementar su fisica(polimorfismo)
    virtual void actualizarFisica(float dt) = 0;
    float obtenerX() const;
    float obtenerY() const;
    float obtenerVelocidadX() const;
    float obtenerVelocidadY() const;
    void establecerX(float x);
    void establecerY(float y);
    void establecerVelocidadX(float vx);
    void establecerVelocidadY(float vy);
};

#endif // ENTIDAD_H