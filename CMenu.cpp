#include "CMenu.h"
#include "funciones.h"
#include <typeinfo>

void CMenu::limpiar(){
  cout << "\033[2J\033[0;0H";
}

void CMenu::ejecutar(){
  
  do{
  CMapa another_one;
  limpiar();
  mapa->imprimirMapa(cout);
  imprimirMenu();
  seleccionarOpcion();
  
  if(m_Opcion!='3'){
  cout<<"¿Deseas salir del programa? "<<endl<<"1. Si\n"<<"2. No\n"<<"Ingrese opcion[1-2]: ";
  cin>>m_Opcion;
  mapa=&another_one;}

  
  }while(m_Opcion=='2');
  salir();
}

void CMenu::imprimirMenu(){
  cout<<"MENU\n";
  cout<<"-----\n\n";
  cout<<"1. Ingresar puntos manualmente\n";
  cout<<"2. Asignar puntos automaticamente\n";
  cout<<"3. Salir\n\n";

}

void CMenu::seleccionarOpcion(){
  char i;
  const char* ptr=&i;
  do{cout<<"Ingrese opcion [1-3]: ";
  cin>>m_Opcion;
  }while((m_Opcion!='1' && m_Opcion!='2' &&m_Opcion!='3') ) ;
  
  switch(m_Opcion){
    case '1':
      ingresarPuntosManualmente();
      break;

    case '2':
      asignarPuntosAutomaticamente();
      break;
  }
}


void CMenu::ingresarPuntosManualmente(){
  coordenada temp_X;
  coordenada temp_Y;
  do{
    cout<<"\nInserte coordenadas de punto de inicio :"<<endl;
    cout<<"\nCoordenada en X (Filas):";
    cin>>temp_X;
    cout<<"\nCoordenada en Y (Columna):";
    cin>>temp_Y;
    if(!(mapa->verificar_coordenada(temp_X, temp_Y))){
      cout<<"\nEsta coordenada no es valida, escribe otra por favor."<<endl;
    }
    }while(mapa->verificar_coordenada(temp_X, temp_Y)==false);

  inicio->set_coordenadas(temp_X, temp_Y);
  mapa->asignarManualInicio(inicio);

  do{
    cout<<"\nInserte coordenadas de punto final;"<<endl;
    cout<<"\nCoordenada en X (Filas):";
    cin>>temp_X;
    cout<<"\nCoordenada en Y (Columna):";
    cin>>temp_Y;
    if(!(mapa->verificar_coordenada(temp_X, temp_Y))){
      cout<<"\nEsta coordenada no es valida, escribe otra por favor."<<endl;
    }
    }while(mapa->verificar_coordenada(temp_X, temp_Y)==false);
  meta->set_coordenadas(temp_X, temp_Y);
  mapa->asignarManualMeta(meta);

  ejecutarManual();
}

void CMenu::ejecutarManual(){
  limpiar();
  mapa->imprimirMapa(cout);
  imprimirMenuManual();
  seleccionarOpcionManual();
}

void CMenu::imprimirMenuManual(){
  cout<<"MENU\n";
  cout<<"-----\n\n";
  cout<<"1. Generar ruta\n";
  cout<<"2. Salir\n\n";

}

void CMenu::seleccionarOpcionManual(){
  do{cout<<"Ingrese opcion [1-2]: ";
  cin>>m_Opcion;}while(m_Opcion!='1' && m_Opcion!='2');
 
  switch(m_Opcion){
    case '1':
      generarRuta();
      break;

    case '2':
      salir();
      break;
  }
}

void CMenu::asignarPuntosAutomaticamente(){
  limpiar();
  mapa->asignarInicio(inicio);
  mapa->asignarMeta(meta);
  ejecutarAutomatico();
}

void CMenu::ejecutarAutomatico(){
  limpiar();
  mapa->imprimirMapa(cout);
  imprimirMenuAutomatico();
  seleccionarOpcionAutomatico(); 
}

void CMenu::imprimirMenuAutomatico(){
  cout<<"MENU\n";
  cout<<"-----\n\n";
  cout<<"1. Reasignar valores\n";
  cout<<"2. Generar ruta\n";
  cout<<"3. Salir\n\n";
}

void CMenu::seleccionarOpcionAutomatico(){
  do{cout<<"Ingrese opcion [1-3]: ";
  cin>>m_Opcion;}while(m_Opcion!='1' && m_Opcion!='2' &&m_Opcion!='3');
  switch(m_Opcion){
    case '1':
      
      reasignarPuntos();
      break;

    case '2':
      generarRuta();
      break;
    
    case '3':
      
      salir();
      break;
  }
}

void CMenu::reasignarPuntos(){
  //SISTEMA PARA REASIGNAR
  caracter opcion;
  CCoordenada temp;
  cout<<"\n1. Reasignar punto inicial"<<endl<<"2. Reasignar punto final "<<endl<<"3. Reasignar ambos "<<endl;

  do
  {
    cout<<"Ingrese opcion [1-3]: ";
    cin>>m_Opcion;
  }while((m_Opcion!='1' && m_Opcion!='2' &&m_Opcion!='3')) ;
  
  coordenada temp_X=0;
  coordenada temp_Y=0;
  switch(m_Opcion){
    case '1':
    temp.setCoodenadas(inicio->get_X(), inicio->get_Y());
    mapa->getCasilla(temp)->setSkin('0');
    
    do{
    cout<<"\nInserte coordenadas de punto de inicio :"<<endl;
    cout<<"\nCoordenada en X (Filas):";
    cin>>temp_X;
    cout<<"\nCoordenada en Y (Columna):";
    cin>>temp_Y;
    if(!(mapa->verificar_coordenada(temp_X, temp_Y)))
    {
      cout<<"\nEsta coordenada no es valida, escribe otra por favor."<<endl;
    }
    }while(mapa->verificar_coordenada(temp_X, temp_Y)==false);

    inicio->set_coordenadas(temp_X, temp_Y);
    
    mapa->asignarManualInicio(inicio);
    break;
    case '2':
    temp.setCoodenadas(meta->get_X(), meta->get_Y());
    mapa->getCasilla(temp)->setSkin('0');
    
    do{
    cout<<"\nInserte coordenadas de punto final;"<<endl;
    cout<<"\nCoordenada en X (Filas):";
    cin>>temp_X;
    cout<<"\nCoordenada en Y (Columna):";
    cin>>temp_Y;
    if(!(mapa->verificar_coordenada(temp_X, temp_Y))){
      cout<<"\nEsta coordenada no es valida, escribe otra por favor."<<endl;
    }
    }while(mapa->verificar_coordenada(temp_X, temp_Y)==false);
    meta->set_coordenadas(temp_X, temp_Y);
    
    mapa->asignarManualMeta(meta);
  
    break;
  
    case '3':
    temp.setCoodenadas(inicio->get_X(), inicio->get_Y());
    mapa->getCasilla(temp)->setSkin('0');
    
    temp.setCoodenadas(meta->get_X(), meta->get_Y());
    mapa->getCasilla(temp)->setSkin('0');
    
    ingresarPuntosManualmente();

    break;}
  ejecutarManual();
}


void CMenu::generarRuta()
{
  PDinamico movil(*inicio); 
  mapa->asignar_pesos(meta);
  while(!estaEnMeta(*mapa, movil))
  {
    mover(*mapa, movil);
  }
  
  mapa->actualizarMapa(movil);
  limpiar();
  
  cout<<"\nResultado: "<<endl;
  mapa->imprimirMapa(cout);

  reporteMovimiento(movil);
  imprimirInforme();
  //salir();
}

void CMenu::imprimirInforme(){
  ifstream reporte;
  string linea;
  reporte.open("Reporte_de_camino.txt");
  while(!reporte.eof())
  {
    getline(reporte,linea);
    cout<<linea<<endl;
  }
}

void CMenu::salir(){
  cout<<"\nSaliendo del programa"<<endl;
}

