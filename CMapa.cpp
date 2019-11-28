#include "Comon.h"
#include "CMapa.h"

letras CMapa::seleccionar_archivo(entero Vi, entero Vf){
  entero ID;
  letras titulo;
  ID = Vi + rand()%(Vf-Vi);
  titulo = ID+'0';
  titulo.push_back('.');
  titulo.push_back('t');
  titulo.push_back('x');
  titulo.push_back('t');
  return titulo;
}

void CMapa::leerArchivo(Casilla*** &matriz, entero filas,                 entero columnas, string direccion_archivo)
{
  ifstream archivo;
  letras lineas;
  entero ID_fila= 0;
  entero valor;

  archivo.open(direccion_archivo, ios::in);
  if(archivo.fail()){
    cout<<"No se encontro la direccion del archivo ";
    exit(1);
  }
  while(!archivo.eof()){
    getline(archivo, lineas);
    for (int j = 0; j < columnas; j++){
      matriz[ID_fila][j]->setEstatus(lineas[j]);
      matriz[ID_fila][j]->setSkin(lineas[j]);
    }
    ID_fila++;
  }
  archivo.close();
}

CMapa::CMapa(){
  filas = 10;
  columnas = 10;

  Tablero = new Casilla** [filas];
  for (int i = 0; i < filas; i++){
    Tablero[i] = new Casilla* [columnas];
    for (int j = 0; j < columnas; j++ ){
      Tablero[i][j] = new Casilla(i, j); 
    }
  srand(time(NULL));
  }

  letras direccion_archivo = "MAPAS/" + seleccionar_archivo(1, 10);

  leerArchivo(Tablero, filas, columnas, direccion_archivo);
}

CMapa::~CMapa(){
  for (int i = 0; i<filas; i++){
    for (int j = 0; j < columnas; j++){
      delete Tablero[i][j];
    }
    delete [] Tablero[i];
  }
  delete [] Tablero;
}

void CMapa::imprimirMapa(ostream& os){
  size_t margenDerecho = 2;
  size_t espaciado = 2;
  
  os << '\n';
  os << setw(margenDerecho) << ' ';
  for (size_t i = 0; i < filas; ++i){
    os << setw(espaciado) << i;
  }
  os << '\n';
  for (size_t i = 0; i < columnas ; ++i) {
    os << setw(margenDerecho) << i;
    for (size_t j = 0; j < 10; ++j) {
      os << setw(espaciado) << Tablero[i][j]->getSkin();//mapa
    }
    os << '\n';
  }
}

void CMapa::imprimirPesos(ostream &os){
  size_t margenDerecho = 2;
  size_t espaciado = 6;
  
  os << '\n';
  os << setw(margenDerecho) << ' ';
  for (size_t i = 0; i < filas; ++i){
    os << setw(espaciado) << i ;
  }
  os << '\n';
  for (size_t i = 0; i < columnas ; ++i) {
    os << setw(margenDerecho) << i;
    for (size_t j = 0; j < 10; ++j) {
      os << setw(espaciado) << Tablero[i][j]->getPeso();//mapa
    }
    os << '\n';
  }
}

void CMapa::asignarInicio(CPunto* inicio){
  entero tempX;
  entero tempY;
 
  do{
    tempX = 0+rand()% (columnas -1);
    tempY = 0+rand()% (filas -1);
  }while(Tablero[tempX][tempY]->getStatus() != '0');

  Tablero[tempX][tempY]->setPunto(inicio);
  Tablero[tempX][tempY]->setEstatus('I');
}

void CMapa::asignarManualInicio(CPunto* inicio){
  entero tempX = inicio->get_X();
  entero tempY = inicio->get_Y();
  Tablero[tempX][tempY]->setPunto(inicio);
  Tablero[tempX][tempY]->setEstatus('I');
}

void CMapa::asignarMeta(CPunto* meta){
  entero tempX;
  entero tempY;

  do{
    tempX = 0+rand()% (columnas -1);
    tempY = 0+rand()% (filas -1);
  }while(Tablero[tempX][tempY]->getStatus() != '0');

  Tablero[tempX][tempY]->setPunto(meta);
  Tablero[tempX][tempY]->setEstatus('F');
  Tablero[tempX][tempY]->setPeso(0);
}

void CMapa::asignarManualMeta(CPunto* meta){
  entero tempX = meta->get_X();
  entero tempY = meta->get_Y();

  Tablero[tempX][tempY]->setPunto(meta);
  Tablero[tempX][tempY]->setEstatus('F');
  Tablero[tempX][tempY]->setPeso(0);
}

void CMapa::asignar_pesos(CPunto* origen){
  coordenada X = origen->get_X(); //filas
  coordenada Y = origen->get_Y(); //columnas
  //sondeo horizontal
  for (int j = 0; j<columnas; j++){
    Tablero[X][j]->setPeso(abs(Y-j));
  }
  //sondeo veritcal
  for(int j = 0; j < columnas; j++){
    entero pesoRef = Tablero[X][j]->getPeso();
    for (int i = X-1; i >= 0; i--){
      if(Tablero[i][j]->getStatus()!='1'){
        Tablero[i][j]->setPeso(pesoRef+1);
      }
      pesoRef++;
    }
    pesoRef = Tablero[X][j]->getPeso();
    for(int i = X+1; i<columnas; i++){
      if(Tablero[i][j]->getStatus()!='1'){
        Tablero[i][j]->setPeso(pesoRef+1);
      }
      pesoRef++;
    }
  }
  
  for(int i = 0; i<filas; i++){
    for (int j = 0; j<columnas; j++){
      if(Tablero[i][j]->getStatus() == '1'){
        Tablero[i][j]->setPeso(10000);
      }
    }
  }
  
}

void CMapa::actualizarMapa(PDinamico& movil){
  if(movil.getHistorial().size()>=1){
    for(int i = 1; i < movil.getHistorial().size()-1; i++){
      getCasilla(movil.getHistorial()[i])->setEstatus('2');
      getCasilla(movil.getHistorial()[i])->setSkin      (movil.get_skin());
    }
  }
}

bool CMapa::verificar_coordenada(entero _x, entero _y){
  if((_x < filas && _y < columnas)||(_x > filas && _y > columnas)){
    if(Tablero[_x][_y]->getStatus()=='0'){
      return true;
    }
  }
  return false;
}