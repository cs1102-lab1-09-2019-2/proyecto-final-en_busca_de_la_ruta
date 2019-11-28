#ifndef PUNTO_H
#define PUNTO_H

#include "Comon.h"
#include "CCordenada.h"

class CPunto{
private: 
  coordenada X;
  coordenada Y;
  mascara skin;

public:
  CPunto () {}
  CPunto(mascara skin):skin(skin){}
  CPunto(coordenada _X,coordenada _Y,mascara skin){
    this-> X = _X;
    this-> Y = _Y;
    this-> skin = skin;
  }

  virtual ~CPunto() = default;

  void set_coordenadas(coordenada _X,coordenada _Y){
  this->X = _X;
  this->Y = _Y;
  }
  void set_skin(mascara _skin){skin = _skin;}

  coordenada get_X() {return X;}
  coordenada get_Y(){return Y;}
  mascara get_skin() {return skin;}
};

/**este es el punto que recorre las partes libres del mapa buscando la meta*/
class PDinamico : public CPunto{
private:
  vector <CCoordenada> historial;
  vector <CCoordenada> salidas; //indica cuales son las rutas libre desde la posicion donde esta
  CCoordenada pos_actual;
public:
  PDinamico(CPunto &otro_punto):CPunto(otro_punto.get_X(), otro_punto.get_Y(), '-'){
    pos_actual.setCoodenadas(otro_punto.get_X(), otro_punto.get_Y());
  }
  
  CCoordenada& getPos_actual(){return pos_actual;}
  
  CCoordenada& getUltimaPos(){return historial[historial.size()-1];}
  
  vector <CCoordenada>& getHistorial(){return historial;}
  vector <CCoordenada>& getSalidas(){return salidas;}
  
  void setPos_actual(CCoordenada _pos){pos_actual = _pos;}
  
  void agregarSalida(CCoordenada _salida){salidas.push_back(_salida);}
  
  void resetearSalida(){salidas.clear();}
  
  void agregarPaso(CCoordenada _paso){
    historial.push_back(_paso);
    pos_actual = _paso;
  }
  
  void eliminarUltimaPos(){historial.pop_back();}

  bool coordenadaEnHistorial(CCoordenada& evaluar);

};
#endif //PUNTO_H;