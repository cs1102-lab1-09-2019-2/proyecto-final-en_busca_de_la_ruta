#ifndef MENU_H
#define MENU_H

#include "Comon.h"
#include "CMapa.h"

class CMenu {
  CPunto* inicio;
  CPunto* meta;
  CMapa* mapa;
  char m_Opcion;
  
  void imprimirMenu();
  void imprimirMenuManual();
  void imprimirMenuAutomatico();

  void seleccionarOpcion();
  void seleccionarOpcionManual();
  void seleccionarOpcionAutomatico();
  
  void ingresarPuntosManualmente();
    
  void asignarPuntosAutomaticamente();
  void reasignarPuntos();

  void generarRuta();
  void salir();
  void limpiar();

  void ejecutarManual();
  void ejecutarAutomatico();
  void imprimirInforme();
public:
    CMenu(CMapa* mapa,CPunto* inicio, CPunto* meta): mapa(mapa), inicio(inicio),meta(meta){}
    
    void ejecutar();
};

#endif //MENU_H