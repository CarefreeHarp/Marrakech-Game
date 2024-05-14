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
struct caracteristicas
{
	posicion pos;
	char hassam;
};
caracteristicas movimiento(char tablero[][7],caracteristicas hassam,posicion adyacentes[]);
caracteristicas mediavuelta(caracteristicas hassam,int i, int casillas);
void UsoAlfombras(char tablero[][7],caracteristicas hassam,posicion adyacentes[], int colorCode);
bool BuscarAlfombras(posicion adyacentes[],alfombra pos_alfombra);
void imprimirtablero(char tablero[][7]);










int main() 
{
    HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );		//linea para poner color
    system("color e0");											//linea cambio de color a fondo amarillo
	color(hConsole, 224);										//linea cambio de color a letra negra y fondo amarillo
    player player1,player2;										//declaracion de variables
    bool ganador=false;
    char tablero[7][7];
    int i,j;
    caracteristicas hassam;
    bool turno=true;
    posicion adyacentes[4];
    
    
    
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
				hassam.pos.posx=j;
				hassam.pos.posy=i;
				hassam.hassam=char(194);
			}
		}
	}
	while(ganador==false)										//mientras no encuentre ganador, se ejecutará todo el juego
	{
		imprimirtablero(tablero);
		if(turno==true)
		{
			cout<<endl<<"Turno de "<<player1.nombre<<" !";
			hassam=movimiento(tablero,hassam,adyacentes);
            imprimirtablero(tablero);
            UsoAlfombras(tablero,hassam,adyacentes,'R');
            turno=false;
		}
		else
		{
			cout<<endl<<"Turno de "<<player2.nombre<<" !";
			hassam=movimiento(tablero,hassam,adyacentes);
            imprimirtablero(tablero);
            UsoAlfombras(tablero,hassam,adyacentes,'A');
            turno=true;
		}
	}

//	color(hConsole, 224);
	return 0;
}




void imprimirtablero(char tablero[][7])																//imprime el tablero
{
	int i,j;
		cout<<char(201)<<char(187)<<"   ";
		for(i=0;i<3;i++)
		{
			cout<<char(201)<<char(205)<<char(205)<<char(205)<<char(187)<<"   ";
		}
		cout<<endl;
		for(i=0;i<7;i++)																    	
		{
			if(i%2==0)
			{
				cout<<char(200);
			}
			else
			{
				cout<<char(201);
			}
			for(j=0;j<7;j++)
			{
				if(j<6)
				{
					cout<<tablero[i][j]<<"   ";
				}
				else
				{
					cout<<tablero[i][j];
				}
			}
			if(i%2==0)
			{
				cout<<char(187);
			}
			else
			{
				cout<<char(188);
			}
			cout<<endl;
			if(i<6)
			{
				if(i%2!=0)
				{
					cout<<char(186);
					cout<<"                         ";
				}
				else
				{
					cout<<"                          ";
					cout<<char(186);
				}
			}
			if(i!=6)
			{
				cout<<endl;	
			}
		}
		cout<<" ";
		for(i=0;i<3;i++)
		{
			if(i!=2)
			{
				cout<<char(200)<<char(205)<<char(205)<<char(205)<<char(188)<<"   ";
			}
			else
			{
				cout<<char(200)<<char(205)<<char(205)<<char(205)<<char(188);	
			}
		}
		cout<<"   "<<char(200)<<char(188);
		cout<<endl;     																		//termina de imprimir el tablero
}





caracteristicas mediavuelta(caracteristicas hassam,int i, int casillas)
{
	bool vueltarealizada=false;
	if(hassam.pos.posx==-1)
	{
	 	cout<<"Hassam se sale por la izquierda del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;										//verificacion de cada una de las posibles salidas del tablero
	 	if(hassam.pos.posy==0)
	 	{
	 		hassam.pos.posx=0;
	 		hassam.hassam=char(194);
	 		hassam.pos.posy+=casillas-i;
	 		hassam.pos.posx+=casillas-i;
	 		vueltarealizada=true;
		}
		if(vueltarealizada==false)
		{
			hassam.hassam=char(195);
			if(hassam.pos.posy%2==0)
			{
				hassam.pos.posy--;
				hassam.pos.posx+=(casillas-i)*2+1;
			}
			else
			{
				hassam.pos.posy++;
				hassam.pos.posx+=(casillas-i)*2+1;
			}
		}
	}	
	else if(hassam.pos.posx==7)
		 {
		 	cout<<"Hassam se sale por la derecha del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;
			if(hassam.pos.posy==6)
     		{
	 			hassam.pos.posx=6;
	 			hassam.hassam=char(193);
	 			hassam.pos.posy-=casillas-i;
	 			hassam.pos.posx-=casillas-i;
	 			vueltarealizada=true;
		  	}
	     	if(vueltarealizada==false)
	     	{
				hassam.hassam=char(180);
				if(hassam.pos.posy%2==0)
				{
					hassam.pos.posy++;
					hassam.pos.posx-=(casillas-i)*2+1;
				}
				else
				{
					hassam.pos.posy--;
					hassam.pos.posx-=(casillas-i)*2+1;
				}
			}
		}
		else if(hassam.pos.posy==-1)
     	 	  {
				 	cout<<"Hassam se sale por arriba del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;										//verificacion de cada una de las posibles salidas del tablero
	 				if(hassam.pos.posx==0)
	 				{
	 					hassam.pos.posy=0;
	 					hassam.hassam=char(195);
	 					hassam.pos.posx+=casillas-i;
	 					hassam.pos.posy+=casillas-i;
	 					vueltarealizada=true;
					}
					if(vueltarealizada==false)
					{
						hassam.hassam=char(194);
						if(hassam.pos.posx%2==0)
						{
							hassam.pos.posx--;
							hassam.pos.posy+=(casillas-i)*2+1;
						}
						else
						{
							hassam.pos.posx++;
							hassam.pos.posy+=(casillas-i)*2+1;
						}
					}
			  }
			  else if(hassam.pos.posy==7)
     			   {
     			   		cout<<"Hassam se sale por abajo del tablero!!"<<endl<<"Se ha hecho un giro!!"<<endl;										//verificacion de cada una de las posibles salidas del tablero
	 					if(hassam.pos.posx==6)
	 					{
	 						hassam.pos.posy=6;
	 						hassam.hassam=char(195);
	 						hassam.pos.posx-=casillas-i;
	 						hassam.pos.posy-=casillas-i;
	 						vueltarealizada=true;
						}
						if(vueltarealizada==false)
						{
							hassam.hassam=char(193);
							if(hassam.pos.posx%2==0)
							{
								hassam.pos.posx++;
								hassam.pos.posy-=(casillas-i)*2+1;
							}
							else
							{
								hassam.pos.posx--;
								hassam.pos.posy-=(casillas-i)*2+1;
							}
						}	
     			   	
		  			}
	return hassam;
}





caracteristicas movimiento(char tablero[][7],caracteristicas hassam,posicion adyacentes[])
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );		//linea para poner color
//	system("color e0");											//linea cambio de color a fondo amarillo
	color(hConsole, 224);										//linea cambio de color a letra negra y fondo amarillo
	int casillas,op=0,direccion;
	int i;
	bool cumple=false;
	srand(time(0));
	cout<<endl<<"Hacia que lado quiere girar a hassam"<<endl<<"Digite 1 si quiere hacia arriba"<<endl<<"Digite 2 si quiere hacia abajo"<<endl<<"Digite 3 si quiere hacia la derecha"<<endl<<"Digite 4 si quiere a la izquierda"<<endl;
	do
	{	color(hConsole, 228);
		cin>>direccion;																																//se pide la direccion en la que se va a mover a hassam
		//color(hConsole, 224);																													
		switch(direccion)																															//se prohibe que gire 180 grados
		{
			case 1: if(hassam.hassam!=char(194))
					{
						tablero[hassam.pos.posy][hassam.pos.posx]=char(0xDB);
						hassam.hassam=char(193);
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;
			case 2:	if(hassam.hassam!=char(193))
					{
						tablero[hassam.pos.posy][hassam.pos.posx]=char(0xDB);
						hassam.hassam=char(194);
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;
			case 3:	if(hassam.hassam!=char(180))
					{
						tablero[hassam.pos.posy][hassam.pos.posx]=char(0xDB);
						hassam.hassam=char(195);
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;
			case 4:	if(hassam.hassam!=char(195))
					{
						tablero[hassam.pos.posy][hassam.pos.posx]=char(0xDB);
						hassam.hassam=char(180);
						cumple=true;
					}
					else
					{
						cout<<"Hassam esta mirando en la direccion contraria y no puede voltear 180 grados, intente de nuevo!"<<endl;
					}
						break;	
			default: cout<<"opcion inexistente"<<endl;
						break;
		}	
	}while(cumple==false);
	cout<<endl<<"Digite 1 para tirar el dado!! "<<endl<<"Recuerde que el minimo numero es 1 y el maximo es 4"<<endl;						//lanzamiento del dado, numero maximo=4, numero minimo=1
	do
	{
		color(hConsole, 228);
		cin>>op;
		color(hConsole, 224);
		switch(op)
		{
			case 1: casillas=(1+rand()%4);
					break;
			default: cout<<"Esa opcion no existe, intente de nuevo"<<endl;
					break;
		}
	}while(op!=1);
	cout<<endl<<"El dado marca el numero "<<casillas<<" !!"<<endl;															
	if(direccion==1)																												//De acuerdo a la direccion, hassam se mueve las casillas marcadas por el dado
	{																																//Por cada paso que da hassam, se verifica si se ha salido del tablero
		for(i=1;i<=casillas;i++)																									//En caso de salida del tablero, hassam dará la vuelta correspondiente
		{
			hassam.pos.posy--;
			hassam=mediavuelta(hassam,i,casillas);	
		}
	}
	else if(direccion==2)
		 {
			for(i=1;i<=casillas;i++)
			{
				hassam.pos.posy++;
				hassam=mediavuelta(hassam,i,casillas);	
			}
		 }
		 else if(direccion==3)
		 	  {
				for(i=1;i<=casillas;i++)
				{
					hassam.pos.posx++;	
					hassam=mediavuelta(hassam,i,casillas);
				}
			  }
			  else
			  {
				for(i=1;i<=casillas;i++)
				{
					hassam.pos.posx--;	
					hassam=mediavuelta(hassam,i,casillas);
				}
			  }
	tablero[hassam.pos.posy][hassam.pos.posx]=hassam.hassam;
	adyacentes[0].posy=hassam.pos.posy+1;
	adyacentes[0].posx=hassam.pos.posx;
	adyacentes[1].posx=hassam.pos.posx+1;
	adyacentes[1].posy=hassam.pos.posy;
	adyacentes[2].posy=hassam.pos.posy-1;
	adyacentes[2].posx=hassam.pos.posx;
	adyacentes[3].posx=hassam.pos.posx-1;
	adyacentes[3].posy=hassam.pos.posy;


	return hassam;
}


void UsoAlfombras(char tablero[][7], caracteristicas hassam, posicion adyacentes[], int colorCode) {
    bool posicionValida = false;
    int eleccion=-1;
	int i,esvalido;
	int NumValido[4]={-1,-1,-1,-1}; 																									// Almacena índices de las opciones válidas
	int idx,ady_x,ady_y;
	
    cout << "Seleccione la posicion inicial para la alfombra adyacente a Hassam (no puede cubrir a Hassam):" << endl;
    esvalido = 0;

    for (i = 0; i < 4; i++) {     																										// Verificar posiciones adyacentes precalculadas
        ady_x = adyacentes[i].posx;
        ady_y = adyacentes[i].posy;
        if (ady_x >= 0 && ady_x < 7 && ady_y >= 0 && ady_y < 7 && tablero[ady_x][ady_y] == char(219)) {
            cout << esvalido << ". (" << ady_x << ", " << ady_y << ") - opcion valida" << endl;
            NumValido[esvalido] = i; 																									// Guardar los índices de las casillas adyacentes válidas
			esvalido++;																						
        }
    }
    cout << "Elija la opcion para la coordenada de la primera mitad de la alfombra (0-" << esvalido-1 << "): ";
    cin >> eleccion;	
    while(eleccion < 0 || eleccion >= esvalido) {
    	cin >> eleccion;																												//eleccion es la posicion del vector donde se guardan los indices de las casillas adyacentes validas
        cout << "Numero de opcion invalido, por favor intente de nuevo." << endl;
    }

    idx = NumValido[eleccion];																											//idx es el índice de la casilla adyacente a hassam eleigda por el usuario
    ady_x = adyacentes[idx].posx;
    ady_y = adyacentes[idx].posy;
    tablero[ady_y][ady_x] = '0';  																										// Colocar la primera mitad de la alfombra
    cout << "Alfombra colocada correctamente en (" << ady_x << ", " << ady_y << ")" << endl;
}





/*
void UsoAlfombras(char tablero[][7],caracteristicas hassam,posicion adyacentes[])
{
    alfombra pos_alfombra;
    int i,j;
    int TableroValores[7][7]{0};
    bool EsAdyacente,SePuede;

    cout<<"Digite donde quiere poner la primera mitad de su alfombra (coordenada x y coordenada y)"<<endl<<"Tenga en cuenta que esta debe ser adyacente a hassam";
    do
    {
        cin>>pos_alfombra.alf1.posx;
        cin>>pos_alfombra.alf1.posy;
        EsAdyacente=BuscarAlfombras(adyacentes,pos_alfombra);
        if(EsAdyacente==false)
        {
            cout<<"Lo siento, no puede poner alfombras aqui, intente de nuevo."<<endl;
        }
    }while(EsAdyacente==false);

    cout<<"Digite donde quiere poner la segunda mitad de su alfombra (coordenada x y coordenada y)"<<endl;

    cin>>pos_alfombra.alf2.posx;
    cin>>pos_alfombra.alf2.posy;

    TableroValores[pos_alfombra.alf1.posx][pos_alfombra.alf1.posy]=1;
    TableroValores[pos_alfombra.alf2.posx][pos_alfombra.alf2.posy]=1;
    //VerificacionAlfombras(adyacentes,hassam,pos_alfombra)





}

bool BuscarAlfombras(posicion adyacentes[],alfombra pos_alfombra)
{
    int i;

    for(i=0;i<4;i++)
    {
        if((adyacentes[i].posy==pos_alfombra.alf1.posy)&&(adyacentes[i].posx==pos_alfombra.alf1.posx))
            return true;
    }
    return false;
*/

/*VerificacionAlfombras(posicion adyacentes[],caracteristicas hassam,alfombra pos_alfombra, alfombra TableroValores[][7])
{

}*/







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

