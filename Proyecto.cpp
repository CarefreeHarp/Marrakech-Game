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
struct posicion
{
	int posx;
	int posy;
};
struct alfombra
{
	posicion alf1;
	posicion alf2;
};
posicion movimiento(char tablero[][7],posicion hassampos);










int main() 
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );		//linea para poner color
    system("color e0");											//linea cambio de color a fondo amarillo
	color(hConsole, 224);										//linea cambio de color a letra negra y fondo amarillo
    player player1,player2;										//declaracion de variables
    bool ganador=false;
    char tablero[7][7];
    int i,j;
    posicion hassampos;
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
				hassampos.posx=j;
				hassampos.posy=i;
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
			hassampos=movimiento(tablero,hassampos);
		}
		else
		{
			cout<<endl<<"Turno de "<<player2.nombre<<" !";
			hassampos=movimiento(tablero,hassampos);
		}
		ganador=true;
	}

//	color(hConsole, 224);
	return 0;
}

posicion movimiento(char tablero[][7],posicion hassampos)
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
	return hassampos;
}

//PONER ALFOMBRAS
// se manda estructura de pos de hassam
//se pide que digite las coordenadas x y de la alfombra que quiere poner
//digite donde quiere poner su alfombra (coord x ,coord y)

//SE LLAMA A VERIFICAR


//VERIFICAR SI SE PUEDE ALFOMBRAS
// if((val_pos_alf1&&val_pos_alf2==a)||(val_pos_alf1&&val_pos_alf2==b)||(val_pos_alf1&&val_pos_alf2==1))||(val_pos_alf1&&val_pos_alf2==2)) VALIDAR CASOS CON ALFOMBRAS
// bool=false;
// intente de nuevo;
// if((alfombra.alf1.posx>7||alfombra.alf1.posy<0)||(alfombra.alf2.posx>7||alfombra.alf2.posy<0))   VALIDAR QUE NO SE SALGAN DE LOS BORDES
// if((posiciondehassam==(alfombra.alf2.posx&&alfombra.alf2.posy))||(posiciondehassam==(alfombra.alf1.posx&&alfombra.alf1.posy))) NO SE PUEDE PONER PORQUE AHI ESTA HASSAM PARA DANIEL: MEJORAR DONDE SE GUARDA POSICION DE HASSAM
// if((alfombra.alf1.posx&&alfombra.alf1.posy)==(alfombra.alf2.posx&&alfombra.alf2.posy)) NO SE PUEDE PONER LAS DOS CASILLAS DE ALFOMBRA EN EL MISMO LUGAR

