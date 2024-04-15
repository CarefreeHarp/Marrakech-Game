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
    
    player1.alfombras=10;										//establecer valores iniciales
    player2.alfombras=10;
    player1.dirhams=20;
    player2.dirhams=20;
	cout<<"Digite el nombre del primer jugador!"<<endl;
	cin>>player1.nombre;
	cout<<"Digite el nombre del segundo jugador!"<<endl;
	cin>>player2.nombre;
	

	color(hConsole, 224);
	return 0;
}
