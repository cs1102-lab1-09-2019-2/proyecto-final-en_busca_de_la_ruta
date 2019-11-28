#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "Comon.h"
#include "CMapa.h"
#include "CCasilla.h"
#include "CPunto.h"

bool haySalida(CMapa& mapa, PDinamico& movil){
  coordenada tempX = movil.getPos_actual().getX();
  coordenada tempY = movil.getPos_actual().getY();
  entero numeroSalidas = 0;
  CCoordenada tempPos;

  if(tempX-1 >= 0){
    tempPos.setCoodenadas(tempX-1,tempY);
    if(mapa.getCasilla(tempPos)->getStatus() != '1'&&!movil.coordenadaEnHistorial(tempPos)){
      numeroSalidas++;
      movil.agregarSalida(tempPos);
    }
  }

  if(tempY-1 >= 0){
    tempPos.setCoodenadas(tempX,tempY-1);
    if(mapa.getCasilla(tempPos)->getStatus() != '1'&&!movil.coordenadaEnHistorial(tempPos)){
      numeroSalidas++;
      movil.agregarSalida(tempPos);
    }
  }

  if(tempX+1 < mapa.getFilas()){
    tempPos.setCoodenadas(tempX+1,tempY);
    if(mapa.getCasilla(tempPos)->getStatus() != '1'&&!movil.coordenadaEnHistorial(tempPos)){
      numeroSalidas++;
      movil.agregarSalida(tempPos);
    }
  }

  if(tempY+1 < mapa.getColumnas()){
    tempPos.setCoodenadas(tempX,tempY+1);
    if(mapa.getCasilla(tempPos)->getStatus() != '1'&&!movil.coordenadaEnHistorial(tempPos)){
      numeroSalidas++;
      movil.agregarSalida(tempPos);
    }
  }

  if(numeroSalidas>=1){
    return true;
  }else{
    return false;
  }
}

CCoordenada buscarPesoMenor(CMapa& mapa, PDinamico& movil){
  CCoordenada salidaMenor;
  entero pesoMenor = 10000;
  entero pesoActual;

  for (auto Salida : movil.getSalidas()){
    pesoActual = mapa.getCasilla(Salida)->getPeso();

    if(movil.getHistorial().size() > 0){
      if(pesoActual < pesoMenor && !movil.coordenadaEnHistorial(Salida)){
        pesoMenor = pesoActual; 
        salidaMenor = Salida;
      }
    }else{
      if(pesoActual < pesoMenor){
        pesoMenor = pesoActual;
        salidaMenor = Salida;
      }
    }
  }
  return salidaMenor;
}

void avanzar(CMapa& mapa, PDinamico& movil){
  movil.agregarPaso(movil.getPos_actual());
  movil.setPos_actual(buscarPesoMenor(mapa , movil));
}

void retroceder(CMapa& mapa, PDinamico& movil){
  CCoordenada ultimaPos(movil.getUltimaPos());
  mapa.getCasilla(movil.getPos_actual())->setPeso(900);
  mapa.getCasilla(movil.getPos_actual())->setEstatus('1');
  movil.setPos_actual(ultimaPos);
  movil.eliminarUltimaPos();
}

void mover(CMapa& mapa, PDinamico& movil){
  entero salidasMin;
  if(haySalida(mapa, movil)){
    avanzar(mapa, movil);
  }else{
    retroceder(mapa, movil);
  }
  movil.resetearSalida();
}

bool estaEnMeta(CMapa& mapa, PDinamico& movil){
  CCoordenada pos = movil.getPos_actual();
  if(mapa.getCasilla(pos) -> getStatus() =='F'){
    movil.agregarPaso(movil.getPos_actual());
    return true;
  }
  return false;
}

void reporteMovimiento(PDinamico& movil){
  ofstream archivo;
  entero num_paso = 0;
  archivo.open("Reporte_de_camino.txt", ios::out);
    archivo<<"\nReporte de camino del movil desde el inicio hasta la meta\n"<<
    "El formato de lectura es coordenada en X y coordenada en Y:"<<endl;
    archivo<<"-----------------------"<<endl;
    archivo<<"|PASO| FILA | COLUMNA |"<<endl;
    archivo<<"-----------------------"<<endl;
  for(auto paso:movil.getHistorial()){
    archivo<<"|"<<setw(3)<<num_paso<<setw(2)<<"|"<<setw(4)<<paso.getX()<<setw(3)<<"|"<<setw(5)<<paso.getY()<<setw(5)<<"|"<<endl;
    archivo<<"-----------------------"<<endl;
    num_paso++;
  }
  archivo.close();
}

ostream& operator << (ostream& os,const CCoordenada& locate){
  os<<locate.getX()<<" : "<<locate.getY()<<endl;
  return os;
}

#endif //FUNCIONES_H