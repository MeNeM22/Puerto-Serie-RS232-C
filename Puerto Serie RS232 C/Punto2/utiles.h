#include<windows.h>
#include<stdlib.h>
#include<string.h>

#define NEGR0 0
#define negro 0

#define AZUL 1
#define azul 1

#define VERDE 2
#define verde 2

#define CYAN 3
#define cyan 3

#define ROJO 4
#define rojo 4

#define PURPURA 5
#define purpura 5

#define AMARILLO 6
#define amarillo 6

#define BLANCO 7
#define blanco 7

#define GRIS 8
#define gris 8

#define AZULB 9
#define azulb 9

#define VERDEB 0xA
#define verdeb 0xA

#define CYANB 0xB
#define cyanb 0xB

#define ROJOB 0xC
#define rojob 0xC

#define PURPURAB 0xD
#define purpurab 0xD

#define AMARILLOB 0xE
#define amarillob 0xE

#define BLANCOB 0xF
#define blancob 0xF







 /*ayuda

 0 = Negro       8 = Gris
 1 = Azul        9 = Azul claro
 2 = Verde       A = Verde claro
 3 = Aguamarina        B = Aguamarina claro
 4 = Rojo        C = Rojo claro
 5 = Púrpura     D = Púrpura claro
 6 = Amarillo    E = Amarillo claro
 7 = Blanco      F = Blanco brillante

*/


void clrscr()
{
    system("cls");

}


void gotoxy(int x,int y)
 {
  COORD coord={0,0};
 coord.X=x;
 coord.Y=y;

 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
 }

 void setcolor(unsigned char CFRE,unsigned char CFON)

   {
       unsigned char atributo;
       char cadcol[20];
       char attrc[3];


       atributo= ((CFON<<4) +CFRE)&0xFF;

       itoa(atributo,attrc,16);

       strcpy(cadcol,"color ");
       strcat(cadcol,attrc);

       //sprintf(cadcol,"color %x",atributo);

       system(cadcol);

   }






