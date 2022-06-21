#include<iostream>
#include<conio.h>
#include "utiles.h"
#include "fserie.h"
using namespace std;

main()
{
    char teclapulsada;
	int puerto;
    cout<<"Presione una tecla:";cin>>teclapulsada;
    cout<<"Ingrese un Puerto COM:";cin>>puerto;
    initserie(puerto,9600);
    
    cambiadtr(false);
    cambiarts(false);
    cambiatxd(0);

    teclapulsada = ' ';
    
    while(cr != 'c')
    {
        if(kbhit() != 0)
        teclapulsada=getch();
        
      if(teclapulsada == 'E')
      {
        cambiarts(true);
      }
      if(teclapulsada == 'X')
      {
        cambiarts(false);
      }

    }
    closeserie();
}
