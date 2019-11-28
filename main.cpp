#include <fstream>
#include "Comon.h"
#include "CMapa.h"
#include "CCasilla.h"
#include "CPunto.h"
#include "CCordenada.h"
#include "CMenu.h"


using namespace std;

int main(){
 
  cout << "\033[2J\033[0;0H";
  srand(time(NULL));
  ifstream archivo;
  string x="2";
  archivo.open("Inicio.txt");
  string gg;
  getline(archivo,gg, 'F');
  cout<<gg;
  cin>>x;

  while(x!="1"){cout<<"Presione 1 para comenzar"<<"m"<<endl; cin>>x;}


  entero opcion;
  CMapa mapa;
  CPunto inicio ('I');
  CPunto meta ('F');

  CMenu menu(&mapa, &inicio, &meta);
  menu.ejecutar();

  return 0;
}