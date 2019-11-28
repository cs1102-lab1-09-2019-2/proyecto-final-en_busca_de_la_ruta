#ifndef MAPA_H
#define MAPA_H

#include "Comon.h"
#include "CCordenada.h"
#include "CPunto.h"
#include "CCasilla.h"


//MAPA
class CMapa{
private:
  entero filas; // = i = X
  entero columnas; // = j = Y
  Casilla ***Tablero;

  string seleccionar_archivo (entero Vi, entero Vf);
  void leerArchivo (Casilla*** &matriz, entero filas, entero columnas,string nombre_archivo);

public:
  CMapa();
  ~CMapa();
  
  entero getFilas(){return this->filas;}
  entero getColumnas(){return this->columnas;}
  
  void modificarCasilla(coordenada X, coordenada Y);
  void imprimirMapa(ostream& os);
  void imprimirPesos(ostream &os);
  void asignarInicio(CPunto* inicio);
  void asignarManualInicio(CPunto* inicio);
  void asignarMeta(CPunto* meta);
  void asignarManualMeta(CPunto* meta);
  
  void asignar_pesos(CPunto* origen);

  void setPesoCasilla(CCoordenada pos, entero peso){
    Tablero[pos.getX()][pos.getY()]->setPeso(peso);
  }
  void actualizarMapa(PDinamico& movil);

  Casilla* getCasilla(CCoordenada location){return Tablero[location.getX()][location.getY()];}

  bool verificar_coordenada(coordenada _x, coordenada _y);

};

#endif //MAPA_H