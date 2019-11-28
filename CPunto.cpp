#include "CPunto.h"

bool PDinamico::coordenadaEnHistorial(CCoordenada& evaluar){
  if(historial.size() >0){
    for(auto paso:historial){
      if(evaluar == paso){
        return true;
      }
    }
  }
  return false;
}

