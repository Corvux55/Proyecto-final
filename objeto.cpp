#include "objeto.h"

Objeto::Objeto(float x, float y, TipoObjeto t):Entidad(x, y), tipo(t), peso(1.0f), activo(false){
}

void Objeto::actualizarFisica(float dt){
   //lo hare despues
}
Objeto::TipoObjeto Objeto::obtenerTipo() const {return tipo;}
bool Objeto::estaActivo() const {return activo;}
float Objeto::obtenerPeso() const {return peso;}