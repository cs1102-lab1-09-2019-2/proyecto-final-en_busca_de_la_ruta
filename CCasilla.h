#ifndef CCASILLA_H
#define CCASILLA_H

#include "Comon.h"
#include "CCordenada.h"
#include "CPunto.h"

class Casilla {
private:
//  coordenada X; //fila
//  coordenada Y; //columna
  CCoordenada ubicacion;
  mascara skin;
  CPunto* pPunto;
  entero peso;
  caracter estatus; //CAMINO(0) //PARED(1)
  
public:
  Casilla (coordenada _X, coordenada _Y, mascara _skin):
  skin(_skin){
    ubicacion.setCoodenadas(_X, _Y);
    estatus = _skin + 0;
  }

  Casilla (coordenada _X, coordenada _Y){
    ubicacion.setCoodenadas(_X, _Y);
  }

  virtual ~Casilla(){}
   
  entero getPeso() {return peso;}
  caracter getStatus() {return estatus;}
  mascara getSkin(){return skin;}
  CCoordenada& getPosicion(){return ubicacion;}
  
  void setEstatus(caracter _estatus){estatus = _estatus;}
  void setSkin(caracter _codigo){skin = _codigo;}
  void setPunto(CPunto* _pPunto){
    pPunto = _pPunto;
    skin = pPunto->get_skin();
    _pPunto -> set_coordenadas(ubicacion.getX(), ubicacion.getY());
  }

  void setPeso(entero _peso){
    peso = _peso;
  }
};
#endif //CCASILLA_H