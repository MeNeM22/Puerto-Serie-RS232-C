#include<iostream>
#include<conio.h>
#include "utiles.h"
#include "fserie.h"
using namespace std;

main()
{

char tp;
int puerto;
setcolor(BLANCOB,AZULB);

gotoxy(1,1);
cout<< "aprete una tecla";cin>>puerto;
initserie(tp,38400);

tp = ' ';
while(tp != 'y')
{
if(tp == 'R')
{
    seriewritestr("?");
}
if(tp == 'S')
{
seriewritestr("5");
}
}
closeserie();
}


