#include <iostream>
#include <windows.h>											//linea para poner color
#include <mmsystem.h>											
#include <ctime>
//#include <cstdlib>
#define color SetConsoleTextAttribute							//linea para poner color
using namespace std;
struct player													//declaracion de player como estructura
{
	string nombre;
	int alfombras;
	int dirhams;
};
struct Desplazamiento
{
	int posx;
	int posy;
};
Desplazamiento movimiento(char tablero[][7],Desplazamiento mov);










int main() 
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );		//linea para poner color
    system("color e0");											//linea cambio de color a fondo amarillo
	color(hConsole, 224);										//linea cambio de color a letra negra y fondo amarillo
    player player1,player2;										//declaracion de variables
    bool ganador=false;
    char tablero[7][7];
    int i,j;
    Desplazamiento mov;
    bool turno=true;
    
    
    
    player1.alfombras=10;										//establecer valores iniciales
    player2.alfombras=10;
    player1.dirhams=20;
    player2.dirhams=20;
	cout<<"Digite el nombre del primer jugador!"<<endl;
	cin>>player1.nombre;
	cout<<"Digite el nombre del segundo jugador!"<<endl;
	cin>>player2.nombre;
	cout<<"SE LE OTORGA 10 ALFOMBRAS Y 10 MONEDAS A CADA JUGADOR!!"<<endl<<endl<<endl<<"HASSAM ESTA REPRESENTADO POR: "<<endl<<"Hassam hacia arriba: "<<char(193)<<endl<<"Hassam hacia la derecha: "<<char(195)<<endl<<"Hassam hacia abajo: "<<char(194)<<endl<<"Hassam hacia la izquierda: "<<char(180)<<endl<<endl<<endl<<"QUE EMPIECE EL JUEGO!!!"<<endl<<endl;
	
	
	for(i=0;i<7;i++)											//llena la matriz de alfombras y coloca a hassam en el medio
	{
		for(j=0;j<7;j++)
		{
			tablero[i][j]=char(0xDB);
			if((i==3)&&(j==3))
			{
				tablero[i][j]=char(194);
				mov.posx=j;
				mov.posy=i;
			}
		}
	}
	while(ganador==false)										//mientras no encuentre ganador, se ejecutará todo el juego
	{
		for(i=0;i<7;i++)										//imprime el tablero
		{
			for(j=0;j<7;j++)
			{
				cout<<tablero[i][j]<<"   ";
			}
			cout<<endl<<endl;
		}
		if(turno==true)
		{
			cout<<endl<<"Turno de "<<player1.nombre<<" !";
			mov=movimiento(tablero,mov);
		}
		else
		{
			cout<<endl<<"Turno de "<<player2.nombre<<" !";
			mov=movimiento(tablero,mov);
		}
		ganador=true;
	}

//	color(hConsole, 224);
	return 0;
}

Desplazamiento movimiento(char tablero[][7],Desplazamiento mov)
{
	int casillas,op=0;
	srand(time(0));
	cout<<endl<<"Hacia que lado quiere girar a hassam";
	cout<<endl<<"Recuerde que el minimo numero es 1 y el maximo es 4"<<endl<<"Digite 1 para tirar el dado!! "<<endl;
	do
	{
		cin>>op;
		switch(op)
		{
			case 1: casillas=(1+rand()%4);
					break;
			default: cout<<"Esa opcion no existe, intente de nuevo"<<endl;
					break;
		}
	}while(op!=1);
	cout<<endl<<"le salio el numero "<<casillas<<" !!";

}
