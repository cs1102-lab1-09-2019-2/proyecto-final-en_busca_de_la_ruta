#ifndef CCORDENADA_H
#define CCORDENADA_H

#include "Comon.h" 

class CCoordenada{
private:
  coordenada X;
  coordenada Y;
public:
  CCoordenada(){}
  CCoordenada(const CCoordenada &other){
    this->X = other.getX();
    this->Y = other.getY();
  }
  CCoordenada(coordenada _X, coordenada _Y):X(_X), Y(_Y){}
  coordenada getX()const {return X;}
  coordenada getY()const {return Y;}
  void setCoodenadas(coordenada _X ,coordenada _Y){
    X = _X;
    Y = _Y;
  }

  bool operator != (const CCoordenada& other){
    return ((this->X != other.getX()|| this->Y != other.getY())?true:false);
  }

  bool operator == (const CCoordenada& other){
    return((this->X == other.getX() && this->Y == other.getY())?true:false);
  }
};

#endif //CCOORDENADA_H