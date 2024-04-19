#include <iostream>
#include <windows.h>											//linea para poner color
#include <mmsystem.h>											//Linea para poner musica
#define color SetConsoleTextAttribute							//linea para poner color
using namespace std;
struct player													//declaracion de player como estructura
{
	string nombre;
	int alfombras;
	int dirhams;
};










int main() 
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );		//linea para poner color
    system("color e0");											//linea cambio de color a fondo amarillo
	color(hConsole, 224);										//linea cambio de color a letra negra y fondo amarillo
    player player1,player2;										//declaracion de variables
    bool ganador=false;
    char tablero[7][7];
    int i,j;
    
    
    
    player1.alfombras=10;										//establecer valores iniciales
    player2.alfombras=10;
    player1.dirhams=20;
    player2.dirhams=20;
	cout<<"Digite el nombre del primer jugador!"<<endl;
	cin>>player1.nombre;
	cout<<"Digite el nombre del segundo jugador!"<<endl;
	cin>>player2.nombre;
	cout<<"SE LE OTORGA 10 ALFOMBRAS Y 10 MONEDAS A CADA JUGADOR!!"<<endl<<endl<<endl<<"HASSAM ESTA REPRESENTADO POR: "<<endl<<"Hassam hacia arriba: "<<char(193)<<endl<<"Hassam hacia la derecha: "<<char(195)<<endl<<"Hassam hacia abajo: "<<char(194)<<endl<<"Hassam hacia la izquierda: "<<char(180)<<endl<<endl<<endl<<"QUE EMPIECE EL JUEGO!!!"<<endl<<endl;
	
	
	for(i=0;i<7;i++)
	{
		for(j=0;j<7;j++)
		{
			tablero[i][j]=char(0xDB);
			if((i==3)&&(j==3))
			{
				tablero[i][j]=char(194);
			}
		}
	}
	while(ganador==false)
	{
		for(i=0;i<7;i++)
		{
			for(j=0;j<7;j++)
			{
				cout<<tablero[i][j]<<"   ";
			}
			cout<<endl<<endl;
		}
		ganador=true;
	}

	color(hConsole, 224);
	return 0;
}
