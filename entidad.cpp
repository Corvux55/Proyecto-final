#include "entidad.h"

Entidad::Entidad(float x, float y):posicionX(x), posicionY(y), velocidadX(0.0f), velocidadY(0.0f) {
}

Entidad::~Entidad(){
}
float Entidad::obtenerX() const{
    return posicionX;
}
float Entidad::obtenerY() const{
    return posicionY;
}
float Entidad::obtenerVelocidadX() const{
    return velocidadX;
}
float Entidad::obtenerVelocidadY() const{
    return velocidadY;
}
void Entidad::establecerX(float x){
    posicionX = x;
}
void Entidad::establecerY(float y){
    posicionY = y;
}
void Entidad::establecerVelocidadX(float vx){
    velocidadX = vx;
}
void Entidad::establecerVelocidadY(float vy) {
    velocidadY = vy;
}